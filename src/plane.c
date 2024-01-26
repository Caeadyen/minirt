/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:59:57 by hrings            #+#    #+#             */
/*   Updated: 2022/11/16 23:22:12 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_hit check_plane_hit(t_minirt *minirt, t_object *obj)
{
	t_hit	result;
	t_plane	*plane;
	double	divisor;
	double t;
	t_vector	tmp;
	plane = (t_plane *)obj->specs;
	result.hit = NO;

	divisor = dot_product(plane->normal, minirt->ray->direction);
	if (divisor == 0)
		return (result);
	tmp = sub_vector(plane->position, minirt->cammera->position);
	t = dot_product(plane->normal, &tmp) / divisor;
	if (t <= 0)
		return (result);
	result.type = OUTSIDE;
	result.distance = t;
	return (result);
}