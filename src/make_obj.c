/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:23:37 by hrings            #+#    #+#             */
/*   Updated: 2022/11/16 23:12:20 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_sphere *make_sphere(t_vector position, double dia, int color)
{
	t_sphere	*sphere;
	t_vector	*coord;
	
	coord = (t_vector *)malloc(sizeof(t_vector));
	if (!coord)
		exit(1);
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	coord->x = position.x;
	coord->y = position.y;
	coord->z = position.z;
	sphere->position = coord;
	sphere->diameter = dia;
	sphere->color = color;
	return (sphere);
}

t_cylinder *make_cylinder(t_vector position, t_vector direction, t_info info)
{
	t_cylinder	*cylinder;
	t_vector	*coord;
	t_vector	*dir;
	
	coord = (t_vector *)malloc(sizeof(t_vector));
	if (!coord)
		exit(1);
	dir = (t_vector *)malloc(sizeof(t_vector));
	if (!dir)
		exit(1);
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		exit(1);
	coord->x = position.x;
	coord->y = position.y;
	coord->z = position.z;
	dir->x = direction.x;
	dir->y = direction.y;
	dir->z = direction.z;
	cylinder->direction = dir;
	cylinder->position = coord;
	cylinder->diameter = info.dia;
	cylinder->height = info.height;
	cylinder->color = info.color;
	cal_ino_cylinder(cylinder);
	return (cylinder);
}

t_plane *make_plane(t_vector position, t_vector normal, int color)
{
	t_plane	*result;

	result = (t_plane *)malloc(sizeof(t_plane));
	if (!result)
		exit(1);
	result->position = (t_vector *)malloc(sizeof(t_vector));
	if (!result->position)
		exit(1);
	result->normal = (t_vector *)malloc(sizeof(t_vector));
	if (!result->normal)
		exit(1);
	assign_vec(result->position, position);
	assign_vec(result->normal, normal);
	result->color = color;
	return (result);
}
