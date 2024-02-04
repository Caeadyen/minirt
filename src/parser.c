/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:31:16 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 21:03:04 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	addvalue(char *str, double num);

double	ft_strtof(t_minirt *minirt, char *str, int error)
{
	double	result;
	int		power;
	int		neg;

	result = 0;
	power = 1;
	neg = 1;
	if (*str == '-')
		neg = -1;
	if (neg == -1)
		str++;
	while (ft_isdigit(*str))
		result = addvalue(str++, result);
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			power *= 10;
			result = addvalue(str++, result);
		}
	}
	if (*str != 0)
		minirt->error = error;
	return (neg * result / (double) power);
}

bool	checkdrange(double value, double min, double max)
{
	if (value > max || value < min)
		return (true);
	return (false);
}

bool	checkirange(int value, int min, int max)
{
	if (value > max || value < min)
		return (true);
	return (false);
}

int	parsecolor(t_minirt *minirt, char *str, int error)
{
	int	r;
	int	b;
	int	g;

	r = -1;
	g = -1;
	b = -1;
	while (ft_isdigit(*str))
		r = addvalue(str++, r);
	if (*str == ',')
		str++;
	while (ft_isdigit(*str))
		g = addvalue(str++, g);
	if (*str == ',')
		str++;
	while (ft_isdigit(*str))
		b = addvalue(str++, b);
	if (checkirange(r, 0, 255) || checkirange(g, 0, 255))
		minirt->error = error;
	if (*str != 0 || checkirange(b, 0, 255))
		minirt->error = error;
	return (get_rgba(r, g, b, 255));
}

t_vector	*parsevector(t_minirt *minirt, char *str, int error)
{
	char		**tmp;
	t_vector	vec;

	tmp = ft_split(str, ',');
	if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] == 0 || tmp[3] != 0)
		minirt->error = error;
	else
	{
		vec.x = ft_strtof(minirt, tmp[0], error);
		vec.y = ft_strtof(minirt, tmp[1], error);
		vec.z = ft_strtof(minirt, tmp[2], error);
	}
	ft_free(tmp);
	return (init_vector(vec));
}

static int	addvalue(char *str, double num)
{
	double	result;

	if (num < 0)
		result = 0;
	else
		result = num;
	result *= 10;
	result += *str - '0';
	return (result);
}
