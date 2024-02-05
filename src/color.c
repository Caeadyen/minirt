/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:54:29 by hrings            #+#    #+#             */
/*   Updated: 2024/02/05 17:49:42 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void averagecolor(t_color *color, int num)
{
	color->r /= num;
	color->g /= num;
	color->b /= num;
}

t_color	initcolor(void)
{
	t_color	result;

	result.r = 0;
	result.b = 0;
	result.g = 0;
	result.a = 255;
	return (result);
}

void	addcolor(t_color *a, t_color b)
{
	a->r += b.r;
	a->b += b.b;
	a->g += b.g;
}

int	decodecolor(t_color *color)
{
	return (get_rgba(color->r, color->g, color->b, color->a));
}
