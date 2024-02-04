/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:21:53 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 18:49:55 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static double	get_t(t_ray *ray, t_cylinder *cylinder);
static double	check_base_hit(t_cylinder *cylinder, t_ray *ray);
static double	check_base_top(t_cylinder *cylinder, t_ray *ray);
static t_hit findcylinderhit(double t, double t3, double t4);
static t_abc	get_abc(t_ray *ray, t_cylinder *cylinder);

t_hit	check_cylinder_hit(t_ray *ray, t_object *obj)
{
	t_cylinder	*cylinder;
	double t;
	double t3;
	double t4;

	cylinder = (t_cylinder *)obj->specs;
	t = get_t(ray, cylinder);
	t3 = check_base_hit(cylinder, ray);
	t4 = check_base_top(cylinder, ray);
	return (findcylinderhit(t,t3,t4));
}

void	cal_ino_cylinder(t_cylinder *cylinder)
{
	t_vector	tmp;
	t_vector	half;

	cylinder->top = (t_vector *)malloc(sizeof(t_vector));
	if (!cylinder->top)
		exit(1);
	cylinder->base = (t_vector *)malloc(sizeof(t_vector));
	if (!cylinder->base)
		exit(1);
	cylinder->axis = (t_vector *)malloc(sizeof(t_vector));
	if (!cylinder->axis)
		exit(1);
	half = scalar_product(cylinder->direction, 0.5 * cylinder->height);
	tmp = sub_vector(cylinder->position, &half);
	assign_vec(cylinder->base, tmp);
	tmp = add_vector(cylinder->position, &half);
	assign_vec(cylinder->top, tmp);
	tmp = sub_vector(cylinder->top, cylinder->base);
	norm_vector(&tmp);
	assign_vec(cylinder->axis, tmp);
}

static double	get_t(t_ray *ray, t_cylinder *cylinder)
{
	t_abc	abc;
	double	t1;
	double	t2;
	double	dis;
	double	max;
	t_vector	point;

	abc = get_abc(ray, cylinder);
	dis = abc.b * abc.b - 4 * abc.a * abc.c;
	if (dis < 0)
		return (-1);
	dis = sqrt(dis);
	t1 = (-abc.b + dis) / (2 * abc.a);
	t2 = (-abc.b - dis) / (2 * abc.a);
	max = sqrt(pow(cylinder->height / 2, 2) + pow(cylinder->diameter, 2));
	point = pointonline(&ray->pos, &ray->direction, t1);
	if (distance(&point, cylinder->position) > max)
		t1 = -1;
	point = pointonline(&ray->pos, &ray->direction, t2);
	if (distance(&point, cylinder->position)  > max)
		t2 = -1;	
	if (t1 < 0 && t2 < 0)
		return (-1);
	else if (t1 < 0 || t2 < 0)
		return (max_double(t1, t2));
	else
		return (min_double(t1, t2));
}

static double	check_base_hit(t_cylinder *cylinder, t_ray *ray)
{
	double	divisor;
	double	t;
	double	d;
	t_vector	tmp;

	divisor = dot_product(cylinder->direction, &ray->direction);
	if (divisor <= 1e-6 && divisor >= -1e-6)
		return (-1);
	tmp = sub_vector(cylinder->base, &ray->pos);
	t = dot_product(cylinder->direction, &tmp) / divisor;
	if (t <= EPSILON)
		return (-1);
	tmp = pointonline(&ray->pos, &ray->direction, t);
	tmp = sub_vector(&tmp, cylinder->base);
	d = dot_product(&tmp, &tmp);
	if (d <= cylinder->diameter * cylinder->diameter)
		return (t);
	else
		return (-1);
}

static double	check_base_top(t_cylinder *cylinder, t_ray *ray)
{
	double	divisor;
	double	t;
	double	d;
	t_vector	tmp;

	divisor = dot_product(cylinder->direction, &ray->direction);
	if (divisor <= 1e-6 && divisor >= -1e-6)
		return (-1);
	tmp = sub_vector(cylinder->top, &ray->pos);
	t = dot_product(cylinder->direction, &tmp) / divisor;
	if (t <= EPSILON)
		return (-1);
	tmp = pointonline(&ray->pos, &ray->direction, t);
	tmp = sub_vector(&tmp, cylinder->top);
	d = dot_product(&tmp, &tmp);
	if (d <= cylinder->diameter * cylinder->diameter)
		return (t);
	else
		return (-1);
}

static t_abc	get_abc(t_ray *ray, t_cylinder *cylinder)
{
	t_abc		result;
	t_vector	w;

	w = sub_vector(&ray->pos, cylinder->position);
	result.a = 1 - pow(dot_product(&ray->direction, cylinder->axis), 2);
	result.b = 2 * (dot_product(&ray->direction, &w) - \
					(dot_product(&ray->direction, cylinder->axis) * \
					dot_product(&w, cylinder->axis)));
	result.c = dot_product(&w, &w) - \
				pow(dot_product(&w, cylinder->axis), 2) - \
				pow(cylinder->diameter, 2);
	return (result);
}

static t_hit findcylinderhit(double t, double t3, double t4)
{
	t_hit	result;

	if (t > 0 && (t < t3 || t3 < 0) && (t < t4 || t4 < 0))
	{
		result.type = MANTLE;
		result.distance = t;
		return (result);
	}
	else if (t3 > 0 && (t3 < t4 || t4 < 0))
	{
		result.type = BASE;
		result.distance = t3;
		return (result);
	}
	else if (t4 > 0)
	{
		result.type = TOP;
		result.distance = t4;
		return (result);
	}
	else
	{
		result.type = NO;
		result.distance = INFINITY;
		return (result);
	}
}