/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:59:57 by hrings            #+#    #+#             */
/*   Updated: 2024/02/03 23:01:27 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_hit check_plane_hit(t_ray *ray, t_object *obj)
{
	t_hit	result;
	t_plane	*plane;
	double	divisor;
	double t;
	t_vector	tmp;
	plane = (t_plane *)obj->specs;
	result.hit = NO;
	result.type = NO;
	//result.distance = INFINITY;
	divisor = dot_product(plane->normal, &ray->direction);
	if (divisor <= 1e-6 && divisor >= -1e-6)
		return (result);
	
	tmp = sub_vector(plane->position, &ray->pos);
	t = dot_product(plane->normal, &tmp) / divisor;
	if (t <= 1e-6)
		return (result);
	result.type = OUTSIDE;
	result.distance = t;
	return (result);
}