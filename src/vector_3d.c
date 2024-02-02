/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:37:26 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 16:38:01 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	*init_vector(t_vector a)
{
	t_vector	*result;

	result = (t_vector *)malloc(sizeof(t_vector));
	if (!result)
		exit(1);
	result->x = a.x;
	result->y = a.y;
	result->z = a.z;
	return (result);
}

t_vector	cross_vector(t_vector *a, t_vector *b)
{
	t_vector	result;

	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	return (result);
}

void	norm_vector(t_vector *a)
{
	double	length;

	length = sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
	a->x = a->x / length;
	a->y = a->y / length;
	a->z = a->z / length;
}

t_vector	scalar_product(t_vector *a, double num)
{
	t_vector	result;

	result.x = a->x * num;
	result.y = a->y * num;
	result.z = a->z * num;
	return (result);
}

double	dot_product(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vector	add_vector(t_vector *a, t_vector *b)
{
	t_vector	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

t_vector	sub_vector(t_vector *a, t_vector *b)
{
	t_vector	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

void	assign_vec(t_vector *a, t_vector b)
{
	a->x = b.x;
	a->y = b.y;
	a->z = b.z;
}

t_vector	ray_point(t_vector *start, t_vector *dir, double t)
{
	t_vector	result;

	result = scalar_product(dir, t);
	result = add_vector(start, &result);
	return (result);
}
