/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:36:51 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 21:13:18 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	checkcolor(int num);

int	addambientlight(t_minirt *minirt, int objectcolor, int color)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color) + ((get_r(objectcolor) + \
		get_r(minirt->amlight->color)) * minirt->amlight->ratio);
	if (r > 255)
		r = 255;
	g = get_g(color) + ((get_g(objectcolor) + \
		get_g(minirt->amlight->color)) * minirt->amlight->ratio);
	if (g > 255)
		g = 255;
	b = get_b(color) + ((get_b(objectcolor) + \
		get_b(minirt->amlight->color)) * minirt->amlight->ratio);
	if (b > 255)
		b = 255;
	return (get_rgba(r, g, b, 255));
}

int	getdiffuselight(t_light *light, t_vector *normal, t_vector *dir, int color)
{
	double	scale;
	int		r;
	int		g;
	int		b;

	scale = dot_product(normal, dir) * light->brightness;
	r = checkcolor(get_r(light->color) * get_r(color) * scale / 255);
	g = checkcolor(get_g(light->color) * get_g(color) * scale / 255);
	b = checkcolor(get_b(light->color) * get_b(color) * scale / 255);
	return (get_rgba(r, g, b, 255));
}

static int	checkcolor(int num)
{
	if (num > 255)
		return (255);
	if (num < 0)
		return (0);
	return (num);
}
