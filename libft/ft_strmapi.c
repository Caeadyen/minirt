/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 21:49:55 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 11:14:10 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	index;
	int				length;

	if (!s)
		return (NULL);
	if (!f)
		return (NULL);
	index = 0;
	length = ft_strlen(s);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (*(s + index))
	{
		*(result + index) = f(index, *(s + index));
		index++;
	}
	result[length] = '\0';
	return (result);
}
