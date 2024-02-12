/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:54:29 by hrings            #+#    #+#             */
/*   Updated: 2024/02/11 22:14:49 by hrings           ###   ########.fr       */
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

void multicolor(t_color *color, double num)
{
	color->r *= num;
	color->g *= num;
	color->b *= num;
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

t_color	initcolorvalue(int color)
{
	t_color	result;

	result.r = get_r(color);
	result.b = get_b(color);
	result.g = get_g(color);
	result.a = get_a(color);
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
	int	r;
	int	g;
	int	b;
	int	a;

	if (color->r > 255)
		r = 255;
	else
		r = color->r;
	if (color->g > 255)
		g = 255;
	else
		g = color->g;
	if (color->b > 255)
		b = 255;
	else
		b = color->b;
	if (color->a > 255)
		a = 255;
	else
		a = 255;	
	return (get_rgba(r, g, b, a));
}
