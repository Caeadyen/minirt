/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:43:55 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 17:38:57 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int		get_color(t_minirt *minirt, t_hit *hit);
static void		get_s_and_dir(t_minirt *minirt, int row, int col);
static t_hit	get_t(double b, double dis);

int	raytracing(t_minirt *minirt, int row, int col)
{
	t_lst_obj	*current;
	t_object	*obj;
	t_hit		hit;
	t_hit		min_hit;

	current = minirt->objects;
	min_hit.distance = INFINITY;
	min_hit.type = NO;
	hit.type = 0;
	hit.distance = 0;
	get_s_and_dir(minirt, row, col);
	while (current)
	{
		obj = current->obj;
		if (obj->type == SPHERE)
			hit = check_sphere_hit(minirt, obj);
		else if (obj->type == CYLINDER)
			hit = check_cylinder_hit(minirt, obj);
		else if (obj->type == PLANE)
			hit = check_plane_hit(minirt, obj);
		if (hit.type && (hit.distance < min_hit.distance))
		{
			min_hit.hit = obj;
			min_hit.distance = hit.distance;
			min_hit.type = hit.type;
		}
		current = current->next;
	}
	if (min_hit.type)
		return (get_color(minirt, &min_hit));
	return (0);
}

t_hit	check_sphere_hit(t_minirt *minirt, t_object *obj)
{
	t_sphere	*sphere;
	t_vector	oc;
	double		b;
	double		c;
	double		dis;

	sphere = obj->specs;
	oc = sub_vector(minirt->camera->position, sphere->position);
	b = dot_product(minirt->ray->direction, &oc);
	c = dot_product(&oc, &oc) - sphere->diameter * sphere->diameter;
	dis = b * b - c;
	return (get_t(b, dis));
}

static int	get_color(t_minirt *minirt, t_hit *hit)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane	*plane;
	t_vector	tmp;
	t_vector	point;
	int result;

	result = 0;
	if (hit->hit->type == SPHERE)
	{
		sphere = (t_sphere *)hit->hit->specs;
		tmp = scalar_product(minirt->ray->direction, hit->distance);
		tmp = add_vector(minirt->camera->position, &tmp);
		tmp = sub_vector(&tmp, sphere->position);
		norm_vector(&tmp);
		result =
			get_rgba(0 , get_r(sphere->color) * ((tmp.y + 1) * 0.5) ,\
			get_g(sphere->color) * ((tmp.y + 1) * 0.5), \
			get_b(sphere->color) * ((tmp.y + 1) * 0.5));
	}
	else if (hit->hit->type == CYLINDER)
	{
		cylinder = (t_cylinder *)hit->hit->specs;
		point = scalar_product(minirt->ray->direction, hit->distance);
		point = add_vector(minirt->camera->position, &point);
		tmp = sub_vector(&point, cylinder->base);
		tmp = scalar_product(cylinder->axis, dot_product(&tmp, cylinder->axis));
		tmp = add_vector(cylinder->base, &tmp);
		tmp = sub_vector(&point, &tmp);
		norm_vector(&tmp);
		result = get_rgba(0 , get_r(cylinder->color) * ((tmp.y + 1) * 0.5) ,\
			get_g(cylinder->color) * ((tmp.y + 1) * 0.5), \
			get_b(cylinder->color) * ((tmp.y + 1) * 0.5));	
	}
	else if (hit->hit->type == PLANE)
	{
		plane = (t_plane *)hit->hit->specs;
		result = plane->color;
	}
		
	return (result);
}

static void	get_s_and_dir(t_minirt *minirt, int row, int col)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;

	a = scalar_product(minirt->ray->u, row);
	b = scalar_product(minirt->ray->v, col);
	c = sub_vector(&a, &b);
	if (minirt->ray->s)
		free(minirt->ray->s);
	a = add_vector(minirt->ray->l, &c);
	minirt->ray->s = init_vector(a);
	if (minirt->ray->direction)
		free(minirt->ray->direction);
	a = sub_vector(minirt->ray->s, minirt->camera->position);
	minirt->ray->direction = init_vector(a);
	norm_vector(minirt->ray->direction);
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
