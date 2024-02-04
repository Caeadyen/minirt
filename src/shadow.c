/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:44:25 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 21:11:29 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	isinshadow(t_minirt *minirt, t_ray *ray)
{
	t_hit		hit;
	double		distance;
	t_lst_obj	*current;
	t_vector	tmp;
	t_object	*obj;

	tmp = sub_vector(minirt->light->position, &ray->pos);
	distance = v_len(&tmp);
	current = minirt->objects;
	while (current)
	{
		obj = current->obj;
		if (obj->type == SPHERE)
			hit = check_sphere_hit(ray, obj);
		else if (obj->type == CYLINDER)
			hit = check_cylinder_hit(ray, obj);
		else if (obj->type == PLANE)
			hit = check_plane_hit(ray, obj);
		if (hit.type != NO && (hit.distance < distance))
			return (true);
		current = current->next;
	}
	return (false);
}
