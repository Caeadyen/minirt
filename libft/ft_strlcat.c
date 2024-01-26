/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:20:53 by hrings            #+#    #+#             */
/*   Updated: 2021/11/12 21:04:07 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	length_dest;
	size_t	length_src;
	size_t	index;

	index = size;
	length_dest = ft_strlen(dest);
	length_src = ft_strlen(src);
	if (length_dest >= size)
		return (length_src + size);
	index = 0;
	while (src[index] && (size-- - length_dest) > 1)
	{
		dest[length_dest + index] = src[index];
		index++;
	}
	dest[length_dest + index] = '\0';
	return (length_dest + length_src);
}
