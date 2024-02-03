/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:23:37 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 20:56:17 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_sphere *make_sphere(t_vector *position, double dia, int color)
{
	t_sphere	*sphere;
	
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->position = position;
	sphere->diameter = dia;
	sphere->color = color;
	return (sphere);
}

t_cylinder *make_cylinder(t_vector *position, t_vector *direction, t_info info)
{
	t_cylinder	*cylinder;
	
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->direction = direction;
	cylinder->position = position;
	cylinder->diameter = info.dia;
	cylinder->height = info.height;
	cylinder->color = info.color;
	cal_ino_cylinder(cylinder);
	return (cylinder);
}

t_plane *make_plane(t_vector *position, t_vector *normal, int color)
{
	t_plane	*result;

	result = (t_plane *)malloc(sizeof(t_plane));
	if (!result)
		exit(1);
	result->position = position;
	result->normal = normal;
	result->color = color;
	return (result);
}
