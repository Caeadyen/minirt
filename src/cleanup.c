/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:08:15 by hrings            #+#    #+#             */
/*   Updated: 2022/11/16 23:14:12 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	free_sphere(t_sphere *sphere);
static void	free_cylinder(t_cylinder *cylinder);
static void	free_plane(t_plane *plane);

void	cleanup(t_object *object)
{
	if (object->type == SPHERE)
		free_sphere((t_sphere *)object->specs);
	else if (object->type == CYLINDER)
		free_cylinder((t_cylinder *)object->specs);
	else if (object->type == PLANE)
		free_plane((t_plane *)object->specs);
	free(object->specs);
	free(object);
}

static void	free_sphere(t_sphere *sphere)
{
	free(sphere->position);
}

static void	free_cylinder(t_cylinder *cylinder)
{
	free(cylinder->position);
	free(cylinder->direction);
	free(cylinder->top);
	free(cylinder->base);
	free(cylinder->axis);
}

static void	free_plane(t_plane *plane)
{
	free(plane->position);
	free(plane->normal);
}

void	clean_up_ray(t_minirt *minirt)
{
	free(minirt->ray->u);
	free(minirt->ray->v);
	free(minirt->ray->l);
	free(minirt->ray->s);
	free(minirt->ray->n);
	free(minirt->ray->direction);
	free(minirt->ray);
}
