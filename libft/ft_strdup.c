/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:01:12 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 15:27:45 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*result;

	length = (size_t) ft_strlen(s) + 1;
	result = (char *) malloc(sizeof(char) * length);
	if (result == NULL)
		return (0);
	result = ft_memcpy(result, s, length);
	return (result);
}
