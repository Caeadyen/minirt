/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 00:19:24 by hrings            #+#    #+#             */
/*   Updated: 2021/11/17 22:08:02 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (*(s + index))
	{
		if (*(s + index) == (char) c)
			return ((char *)(s + index));
		index++;
	}
	if (!c)
		return ((char *)(s + index));
	return (NULL);
}
