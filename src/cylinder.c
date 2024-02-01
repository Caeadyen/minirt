/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:21:53 by hrings            #+#    #+#             */
/*   Updated: 2024/02/01 11:16:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_hit	get_t(double a, double b, double c);
static t_hit	check_base_hit(t_minirt *minirt, t_cylinder *cylinder);
static t_hit	check_base_top(t_minirt *minirt, t_cylinder *cylinder);
static t_abc	get_abc(t_minirt *minirt, t_cylinder *cylinder);

t_hit	check_cylinder_hit(t_minirt *minirt, t_object *obj)
{
	t_cylinder	*cylinder;
	t_vector	point;
	t_hit		result;
	t_abc		abc;
	double		tmp;

	cylinder = (t_cylinder *)obj->specs;
	abc = get_abc(minirt, cylinder);
	result = get_t(abc.a, abc.b, abc.c);
	if (result.type == NO)
		return (result);
	point = ray_point(minirt->camera->position, minirt->ray->direction, \
					result.distance);
	point = sub_vector(&point, cylinder->base);
	tmp = dot_product(&point, cylinder->axis);
	if (tmp < 0)
		return (check_base_hit(minirt, cylinder));
	else if (tmp > cylinder->height)
		return (check_base_top(minirt, cylinder));
	else
		result.where = MANTLE;
	return (result);
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

static t_hit	get_t(double a, double b, double c)
{
	t_hit	result;
	double	result1;
	double	result2;
	double	dis;

	dis = b * b - 4 * a * c;
	result.type = NO;
	if (dis < 0)
		return (result);
	dis = sqrt(dis);
	result1 = (-b + dis) / (2 * a);
	result2 = (-b - dis) / (2 * a);
	if (result1 < 0 && result2 < 0)
		result.type = NO;
	else if (result1 < 0 || result2 < 0)
	{
		result.type = INSIDE;
		result.distance = max_double(result1, result2);
	}
	else
	{
		result.type = OUTSIDE;
		result.distance = min_double(result1, result2);
	}
	return (result);
}

t_hit	check_base_hit(t_minirt *minirt, t_cylinder *cylinder)
{
	t_hit	result;

	result.type = NO;
	result.where = BASE;
	result.distance = minirt->height * cylinder->height;
	return (result);
}

t_hit	check_base_top(t_minirt *minirt, t_cylinder *cylinder)
{
	t_hit	result;

	result.type = NO;
	result.where = TOP;
	result.distance = minirt->height * cylinder->height;
	return (result);
}

static t_abc	get_abc(t_minirt *minirt, t_cylinder *cylinder)
{
	t_abc		result;
	t_vector	w;

	w = sub_vector(minirt->camera->position, cylinder->position);
	result.a = 1 - pow(dot_product(minirt->ray->direction, cylinder->axis), 2);
	result.b = 2 * (dot_product(minirt->ray->direction, &w) - \
					(dot_product(minirt->ray->direction, cylinder->axis) * \
					dot_product(&w, cylinder->axis)));
	result.c = dot_product(&w, &w) - \
				pow(dot_product(&w, cylinder->axis), 2) - \
				pow(cylinder->diameter, 2);
	return (result);
}
