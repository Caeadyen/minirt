/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:03:42 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 23:48:38 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n);
static void		fill_str(int number, size_t d, size_t off, char *result);

char	*ft_itoa(int n)
{
	char	*result;
	int		number;
	size_t	digits;
	size_t	offset;

	number = (unsigned int) n;
	digits = get_digits(n);
	result = (char *)malloc((digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n >= 0)
	{
		offset = 0;
		fill_str(number, digits, offset, result);
	}
	else
	{
		offset = 1;
		fill_str(number, digits, offset, result);
		result[0] = '-';
	}
	result[digits] = '\0';
	return (result);
}

static size_t	get_digits(int n)
{
	size_t	digits_r;

	digits_r = 1;
	if (n < 0)
		digits_r++;
	while (n > 9 || n < -9)
	{
		n /= 10;
		digits_r++;
	}
	return (digits_r);
}

static void	fill_str(int number, size_t d, size_t o, char *result)
{
	while (d > o)
	{
		if (number < 0)
		{
			result[--d] = -(number % 10) + '0';
			number /= 10;
		}
		else
		{
			result[--d] = (number % 10) + '0';
			number /= 10;
		}
	}
}
