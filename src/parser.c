/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:31:16 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 16:53:03 by hrings           ###   ########.fr       */
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

static int	addvalue(char *str, double num)
{
	double	result;

	result = num;
	result *= 10;
	result += *str - '0';
	return (result);
}
