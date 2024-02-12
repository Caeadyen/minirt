/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:36:51 by hrings            #+#    #+#             */
/*   Updated: 2024/02/11 23:46:37 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	checkcolor(int num);

t_color	addambientlight(t_minirt *minirt, double ambient, int objcolor, t_color *color)
{
	t_color	result;
	double scale;

	scale = minirt->amlight->ratio * ambient;
	result.r = get_r(minirt->amlight->color) * get_r(objcolor) * scale / 255 + color->r;
	result.g = get_g(minirt->amlight->color) * get_g(objcolor) * scale / 255 + color->g;
	result.b = get_b(minirt->amlight->color) * get_b(objcolor) * scale / 255 + color->b;
	result.a = get_a(minirt->amlight->color) * get_a(objcolor) * scale / 255 + color->a;
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
