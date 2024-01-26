/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:33:44 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 00:23:03 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	s_i;
	size_t	f_i;

	if (*to_find == '\0')
		return ((char *)str);
	s_i = 0;
	while (str[s_i] != '\0' && s_i < n)
	{
		f_i = 0;
		while (str[s_i + f_i] == to_find[f_i] && s_i + f_i < n)
		{
			if (to_find[f_i + 1] == '\0')
				return ((char *)(str + s_i));
			f_i++;
		}
		s_i++;
	}
	return (0);
}
