/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:09:34 by hrings            #+#    #+#             */
/*   Updated: 2021/11/17 22:08:18 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;

	index = (size_t) ft_strlen(s);
	if (*(s + index) == c)
		return ((char *)(s + index));
	while (index > 0)
	{
		index--;
		if (*(s + index) == (char) c)
			return ((char *)(s + index));
	}
	return (NULL);
}
