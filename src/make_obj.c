/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:23:37 by hrings            #+#    #+#             */
/*   Updated: 2024/02/11 18:37:38 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_sphere	*make_sphere(t_vector *position, t_info_sp info)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->position = position;
	sphere->diameter = info.dia;
	sphere->color = info.color;
	sphere->material = info.mat;
	sphere->ks = info.ks;
	sphere->kd = info.kd;
	sphere->ka = info.ka;
	sphere->n = info.n;
	return (sphere);
}

t_cylinder	*make_cylinder(t_vector *position, t_vector *direction, t_info_cy info)
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
	cylinder->material = info.mat;
	cylinder->ks = info.ks;
	cylinder->kd = info.kd;
	cylinder->ka = info.ka;
	cylinder->n = info.n;
	cal_ino_cylinder(cylinder);
	return (cylinder);
}

t_plane	*make_plane(t_vector *position, t_vector *normal, t_info_pl info)
{
	t_plane	*result;

	result = (t_plane *)malloc(sizeof(t_plane));
	if (!result)
		exit(1);
	result->position = position;
	result->normal = normal;
	result->color = info.color;
	result->material = info.mat;
	result->ks = info.ks;
	result->kd = info.kd;
	result->ka = info.ka;
	result->n = info.n;
	return (result);
}
