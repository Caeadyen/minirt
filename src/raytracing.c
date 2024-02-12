/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:43:55 by hrings            #+#    #+#             */
/*   Updated: 2024/02/12 01:33:48 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_color	get_color(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_hit	get_t(double b, double dis);
static t_color	getspherecolor(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_color	getplanecolor(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_color	getcylindercolor(t_minirt *minirt, t_ray *ray, t_hit *hit);
static int		gethitmat(t_hit *hit);
static t_ray	newray(t_ray *ray, t_hit *hit);
static t_colors	initresultcolor(void);
static t_color	sumuplights(t_colors *colors);
static t_vector	reflection(t_ray *ray, t_vector *normal);
static t_color	getdiffuselightsp(t_light *light, t_vectors *vectors, t_sphere *sphere);
static t_color	getdiffuselightpl(t_light *light, t_vectors *vectors, t_plane *plane);
static t_color	getdiffuselightcy(t_light *light, t_vectors *vectors, t_cylinder *cylinder);

t_color	raytracing(t_minirt *minirt, t_ray *ray, int depth)
{
	t_lst_obj	*current;
	t_object	*obj;
	t_hit		hit;
	t_hit		min_hit;
	int			mat;
	t_ray		secray;
	t_color		light;
	t_colors	result;
	

	if (depth <= 0)
		return (initcolor());
	result = initresultcolor();
	current = minirt->objects;
	min_hit.distance = INFINITY;
	min_hit.type = NO;
	min_hit.hit = NULL;
	hit.type = NO;
	hit.distance = INFINITY;
	while (current)
	{
		obj = current->obj;
		if (obj->type == SPHERE)
			hit = check_sphere_hit(ray, obj);
		else if (obj->type == CYLINDER)
			hit = check_cylinder_hit(ray, obj);
		else if (obj->type == PLANE)
			hit = check_plane_hit(ray, obj);
		if (hit.type != NO && (hit.distance < min_hit.distance))
		{
			min_hit.hit = obj;
			min_hit.distance = hit.distance;
			min_hit.type = hit.type;
		}
		current = current->next;
	}
	if (!min_hit.type)
		return (initcolor());
	mat = gethitmat(&min_hit);
	if (mat == NORMAL)
	{
		result.phong = get_color(minirt, ray, &min_hit);
	}
		
	else if (mat == REFLECTIVE)
	{
		secray = newray(ray, &min_hit);
		light = raytracing(minirt, &secray, depth - 1);
		averagecolor(&light, 2);
		result.reflect = light;
	}
	else if (mat == REFRACTIVE)
	{
		secray = newray(ray, &min_hit);
		light = raytracing(minirt, &secray, depth - 1);
		averagecolor(&light, 2);
		result.refracted = light;
	}
	return (sumuplights(&result));
}

static t_ray	newray(t_ray *ray, t_hit *hit)
{
	t_ray		result;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_vector	normal;
	double		len;

	result.pos = pointonline(&ray->pos, &ray->direction, hit->distance);
	if (hit->hit->type == SPHERE)
	{
		sphere = hit->hit->specs;
		normal = sub_vector(&result.pos, sphere->position);
		norm_vector(&normal);
	}
	else if (hit->hit->type == CYLINDER)
	{
		cylinder = hit->hit->specs;
		if (hit->type == MANTLE)
		{
			normal = sub_vector(&result.pos, cylinder->base);
			normal = scalar_product(cylinder->axis, dot_product(&normal, cylinder->axis));
			normal = add_vector(cylinder->base, &normal);
			normal = sub_vector(&result.pos, &normal);
			norm_vector(&normal);
		}
		else if (hit->type == TOP)
			normal = scalar_product(cylinder->direction, 1);
		else if (hit->type == BASE)
			normal = scalar_product(cylinder->direction, -1);
	}
	else if (hit->hit->type == PLANE)
	{
		plane = hit->hit->specs;
		if (dot_product(&ray->direction, plane->normal) < 0)
			normal = scalar_product(plane->normal, 1);
		else
			normal = scalar_product(plane->normal, -1);
	}
	else
		exit(1);
	result.pos = pointonline(&result.pos, &normal, EPSILON);
	len = dot_product(&ray->direction, &normal) * 2;
	result.direction = scalar_product(&normal, len);
	result.direction = sub_vector(&ray->direction, &result.direction);
	return (result);
}

t_hit	check_sphere_hit(t_ray *ray, t_object *obj)
{
	t_sphere	*sphere;
	t_vector	oc;
	double		b;
	double		c;
	double		dis;

	sphere = obj->specs;
	oc = sub_vector(&ray->pos, sphere->position);
	b = dot_product(&ray->direction, &oc);
	c = dot_product(&oc, &oc) - sphere->diameter * sphere->diameter;
	dis = b * b - c;
	return (get_t(b, dis));
}

static t_color	get_color(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_color	result;

	result = initcolor();
	if (hit->hit->type == SPHERE)
		result = getspherecolor(minirt, ray, hit);
	else if (hit->hit->type == CYLINDER)
		result = getcylindercolor(minirt, ray, hit);
	else if (hit->hit->type == PLANE)
		result = getplanecolor(minirt, ray, hit);
	return (result);
}

static t_hit	get_t(double b, double dis)
{
	t_hit	result;
	double	result1;
	double	result2;

	result.type = NO;
	if (dis < 0)
		return (result);
	result1 = sqrt(dis);
	result2 = -b - result1;
	result1 -= b;
	if (result1 < 0 && result2 < 0)
		return (result);
	result.type = INSIDE;
	if (result1 < 0)
		result.distance = result2;
	else if (result2 < 0)
		result.distance = result1;
	else
	{
		result.type = OUTSIDE;
		result.distance = min_double(result1, result2);
	}
	return (result);
}

static t_color	getspherecolor(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_sphere	*sphere;
	t_ray		lightray;
	t_color		result;
	t_vectors	tmp;
	
	sphere = (t_sphere *)hit->hit->specs;
	lightray.pos = pointonline(&ray->pos, &ray->direction, hit->distance);
	tmp.norm = sub_vector(&lightray.pos, sphere->position);
	norm_vector(&tmp.norm);
	lightray.pos = pointonline(&lightray.pos, &tmp.norm, EPSILON);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (isinshadow(minirt, &lightray))
	{
		result = initcolor();
	}
	else
	{
		tmp.reflec = reflection(&lightray, &tmp.norm);
		tmp.light = lightray.direction;
		tmp.dir = ray->direction;
		result = getdiffuselightsp(minirt->light, &tmp, sphere);
	}
	return (addambientlight(minirt, sphere->ka, sphere->color, &result));
}

static t_color	getplanecolor(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_plane		*plane;
	t_ray		lightray;
	t_color		result;
	t_vectors	tmp;

	plane = (t_plane *)hit->hit->specs;
	if (dot_product(&ray->direction, plane->normal) < 0)
		tmp.norm = scalar_product(plane->normal, 1);
	else
		tmp.norm = scalar_product(plane->normal, -1);
	lightray.pos = pointonline(&ray->pos, &ray->direction, hit->distance);
	lightray.pos = pointonline(&lightray.pos, &tmp.norm, EPSILON);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (isinshadow(minirt, &lightray))
	{
		result = initcolor();
	}
	else
	{
		tmp.reflec = reflection(&lightray, &tmp.norm);
		tmp.light = lightray.direction;
		tmp.dir = ray->direction;
		result = getdiffuselightpl(minirt->light, &tmp, plane);
	}
	return (addambientlight(minirt, plane->ka, plane->color, &result));
}

static t_color	getcylindercolor(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_cylinder	*cylinder;	
	t_vectors	tmp;
	t_ray		lightray;
	t_color		result;

	cylinder = (t_cylinder *)hit->hit->specs;
	lightray.pos = pointonline(&ray->pos, &ray->direction, hit->distance);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (hit->type == MANTLE)
	{
		tmp.norm = sub_vector(&lightray.pos, cylinder->base);
		tmp.norm = scalar_product(cylinder->axis, dot_product(&tmp.norm, cylinder->axis));
		tmp.norm = add_vector(cylinder->base, &tmp.norm);
		tmp.norm = sub_vector(&lightray.pos, &tmp.norm);
		norm_vector(&tmp.norm);
	}
	else if (hit->type == TOP)
		tmp.norm = scalar_product(cylinder->direction, 1);
	else if (hit->type == BASE)
		tmp.norm = scalar_product(cylinder->direction, -1);
	lightray.pos = pointonline(&lightray.pos, &tmp.norm, EPSILON);
	if (isinshadow(minirt, &lightray))
	{
		result = initcolor();
	}
	else
	{
		tmp.reflec = reflection(&lightray, &tmp.norm);
		tmp.light = lightray.direction;
		tmp.dir = ray->direction;
		result = getdiffuselightcy(minirt->light, &tmp, cylinder);
	}
	return (addambientlight(minirt, cylinder->ka, cylinder->color, &result));
}

static int	gethitmat(t_hit *hit)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (!hit->type)
		return (0);
	else if (hit->hit->type == SPHERE)
	{
		sphere = hit->hit->specs;
		return (sphere->material);
	}
	else if (hit->hit->type == CYLINDER)
	{
		cylinder = hit->hit->specs;
		return (cylinder->material);
	}
	else if (hit->hit->type == PLANE)
	{
		plane = hit->hit->specs;
		return (plane->material);
	}
	return (-1);
}

static t_colors	initresultcolor(void)
{
	t_colors	result;

	result.phong = initcolor();
	result.reflect = initcolor();
	result.refracted = initcolor();
	return (result);
}

static t_color	sumuplights(t_colors *colors)
{
	t_color	result;

	result.r = colors->phong.r + colors->reflect.r + colors->refracted.r;
	if (result.r > 255)
		result.r = 255;
	result.g = colors->phong.g + colors->reflect.g + colors->refracted.g;
	if (result.g > 255)
		result.g = 255;
	result.b = colors->phong.b + colors->reflect.b + colors->refracted.b;
	if (result.b > 255)
		result.b = 255;
	result.a = colors->phong.a + colors->reflect.a + colors->refracted.a;
	if (result.a > 255)
		result.a = 255;
	return (result);
}

static t_vector	reflection(t_ray *ray, t_vector *normal)
{
	t_vector	result;
	double		len;

	len = dot_product(&ray->direction, normal) * 2;
	result = scalar_product(normal, len);
	result = sub_vector(&ray->direction, &result);
	norm_vector(&result);
	return (result);
}

static t_color	getdiffuselightsp(t_light *light, t_vectors *vectors, t_sphere *sphere)
{
	t_color	result;
	t_color	specclight;
	double	diffuse;
	double	specc;

	diffuse = max_double(0, dot_product(&vectors->light, &vectors->norm) * sphere->kd);
	specc = max_double(0, pow(dot_product(&vectors->reflec, &vectors->dir), sphere->n) * ((sphere->n + 2) / (2 * M_PI)) * sphere->ks);
	result = initcolorvalue(sphere->color);
	specclight = initcolorvalue(light->color);
	result.r = specclight.r * (diffuse * result.r / 255 + specc);
	result.g = specclight.g * (diffuse * result.g / 255 + specc);
	result.b = specclight.b * (diffuse * result.b / 255 + specc);
	result.a = 255;
	return (result);
}

static t_color	getdiffuselightpl(t_light *light, t_vectors *vectors, t_plane *plane)
{
	t_color	result;
	t_color	specclight;
	double	diffuse;
	double	specc;

	diffuse = max_double(0, dot_product(&vectors->light, &vectors->norm) * plane->kd);
	specc = max_double(0, pow(dot_product(&vectors->reflec, &vectors->dir), plane->n) * ((plane->n + 2) / (2 * M_PI)) * plane->ks);
	result = initcolorvalue(plane->color);
	specclight = initcolorvalue(light->color);
	result.r = specclight.r * (diffuse * result.r / 255 + specc);
	result.g = specclight.g * (diffuse * result.g / 255 + specc);
	result.b = specclight.b * (diffuse * result.b / 255 + specc);
	result.a = 255;
	return (result);
}

static t_color	getdiffuselightcy(t_light *light, t_vectors *vectors, t_cylinder *cylinder)
{
	t_color	result;
	t_color	specclight;
	double	diffuse;
	double	specc;

	diffuse = max_double(0, dot_product(&vectors->light, &vectors->norm) * cylinder->kd);
	specc = max_double(0, pow(dot_product(&vectors->reflec, &vectors->dir), cylinder->n) * ((cylinder->n + 2) / (2 * 3.41)) * cylinder->ks);
	result = initcolorvalue(cylinder->color);
	specclight = initcolorvalue(light->color);
	result.r = specclight.r * (diffuse * result.r / 255 + specc);
	result.g = specclight.g * (diffuse * result.g / 255 + specc);
	result.b = specclight.b * (diffuse * result.b / 255 + specc);
	result.a = 255;
	return (result);
}
