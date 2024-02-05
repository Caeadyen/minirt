/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:43:55 by hrings            #+#    #+#             */
/*   Updated: 2024/02/05 17:30:19 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_color	get_color(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_hit	get_t(double b, double dis);
static t_color	getspherecolor(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_color	getplanecolor(t_minirt *minirt, t_ray *ray, t_hit *hit);
static t_color	getcylindercolor(t_minirt *minirt, t_ray *ray, t_hit *hit);

t_color	raytracing(t_minirt *minirt, t_ray *ray)
{
	t_lst_obj	*current;
	t_object	*obj;
	t_hit		hit;
	t_hit		min_hit;

	current = minirt->objects;
	min_hit.distance = INFINITY;
	min_hit.type = NO;
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
	if (min_hit.type)
		return (get_color(minirt, ray, &min_hit));
	return (initcolor());
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
	t_vector	tmp;
	t_vector	normal;
	t_ray		lightray;
	t_color		result;

	sphere = (t_sphere *)hit->hit->specs;
	tmp = scalar_product(&ray->direction, hit->distance);
	lightray.pos = add_vector(&ray->pos, &tmp);
	normal = sub_vector(&lightray.pos, sphere->position);
	norm_vector(&normal);
	tmp = scalar_product(&normal, EPSILON);
	lightray.pos = add_vector(&lightray.pos, &tmp);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (isinshadow(minirt, &lightray))
		result = initcolor();
	else
		result = getdiffuselight(minirt->light, &normal, &lightray.direction, sphere->color);
	return (addambientlight(minirt, sphere->color, &result));
}

static t_color	getplanecolor(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_plane		*plane;
	t_vector	tmp;
	t_ray		lightray;
	t_vector	normal;
	t_color		result;

	plane = (t_plane *)hit->hit->specs;
	if (dot_product(&ray->direction, plane->normal) < 0)
		normal = scalar_product(plane->normal, 1);
	else
		normal = scalar_product(plane->normal, -1);
	tmp = scalar_product(&ray->direction, hit->distance);
	lightray.pos = add_vector(&ray->pos, &tmp);
	tmp = scalar_product(&normal, EPSILON);
	lightray.pos = add_vector(&lightray.pos, &tmp);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (isinshadow(minirt, &lightray))
		result = initcolor();
	else
		result = getdiffuselight(minirt->light, &normal, &lightray.direction, plane->color);
	return (addambientlight(minirt, plane->color, &result));
}

static t_color	getcylindercolor(t_minirt *minirt, t_ray *ray, t_hit *hit)
{
	t_cylinder	*cylinder;	
	t_vector	normal;
	t_ray		lightray;
	t_color		result;

	cylinder = (t_cylinder *)hit->hit->specs;
	lightray.pos = pointonline(&ray->pos, &ray->direction, hit->distance);
	lightray.direction = sub_vector(minirt->light->position, &lightray.pos);
	norm_vector(&lightray.direction);
	if (hit->type == MANTLE)
	{
		normal = sub_vector(&lightray.pos, cylinder->base);
		normal = scalar_product(cylinder->axis, dot_product(&normal, cylinder->axis));
		normal = add_vector(cylinder->base, &normal);
		normal = sub_vector(&lightray.pos, &normal);
		norm_vector(&normal);
	}
	else if (hit->type == TOP)
		normal = scalar_product(cylinder->direction, 1);
	else if (hit->type == BASE)
		normal = scalar_product(cylinder->direction, -1);
	lightray.pos = pointonline(&lightray.pos, &normal, EPSILON);
	if (isinshadow(minirt, &lightray))
		result = initcolor();
	else
		result = getdiffuselight(minirt->light, &normal, &lightray.direction, cylinder->color);
	return (addambientlight(minirt, cylinder->color, &result));
}
