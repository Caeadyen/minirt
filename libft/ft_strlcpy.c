/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:12:00 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 23:45:48 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	src_size;

	index = 0;
	src_size = 0;
	while (src[index] != '\0')
	{
		src_size++;
		index++;
	}
	if (size == 0)
		return (src_size);
	index = 0;
	while (index < (size - 1) && *src != '\0')
	{
		dest[index] = *src;
		index++;
		src++;
	}
	dest[index] = '\0';
	return (src_size);
}
