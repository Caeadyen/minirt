/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:36:51 by hrings            #+#    #+#             */
/*   Updated: 2024/02/06 22:11:18 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	checkcolor(int num);

t_color	addambientlight(t_minirt *minirt, int objectcolor, t_color *color)
{
	t_color	result;

	result.r = color->r + ((get_r(objectcolor) + \
		get_r(minirt->amlight->color)) * minirt->amlight->ratio);
	if (result.r > 255)
		result.r = 255;
	result.g = color->g + ((get_g(objectcolor) + \
		get_g(minirt->amlight->color)) * minirt->amlight->ratio);
	if (result.g > 255)
		result.g = 255;
	result.b = color->b + ((get_b(objectcolor) + \
		get_b(minirt->amlight->color)) * minirt->amlight->ratio);
	if (result.b > 255)
		result.b = 255;
	result.a = 255;
	return (result);
}

t_color	getdiffuselight(t_light *light, t_vector *normal, t_vector *dir, int color)
{
	double	scale;
	t_color	result;

	scale = dot_product(normal, dir) * light->brightness;
	result.r = checkcolor(get_r(light->color) * get_r(color) * scale / 255);
	result.g = checkcolor(get_g(light->color) * get_g(color) * scale / 255);
	result.b = checkcolor(get_b(light->color) * get_b(color) * scale / 255);
	result.a = 255;
	return (result);
}

static int	checkcolor(int num)
{
	if (num > 255)
		return (255);
	if (num < 0)
		return (0);
	return (num);
}
