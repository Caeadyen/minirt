/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:07:32 by hrings            #+#    #+#             */
/*   Updated: 2021/11/17 22:57:53 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	index;
	size_t	length;

	if (!s)
		return (NULL);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (length < len)
		len = length;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	while (index < len)
	{
		result[index] = s[index + start];
		index++;
	}
	result[index] = '\0';
	return (result);
}
