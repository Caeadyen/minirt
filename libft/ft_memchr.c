/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:59:56 by hrings            #+#    #+#             */
/*   Updated: 2021/11/15 23:51:33 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	*s;

	s = (unsigned char *) src;
	index = 0;
	while (index < n)
	{
		if (*(s + index) == (unsigned char) c)
			return (s + index);
		index++;
	}
	return (0);
}
