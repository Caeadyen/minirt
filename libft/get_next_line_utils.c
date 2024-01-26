/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:58:10 by hrings            #+#    #+#             */
/*   Updated: 2022/02/03 10:45:30 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*result;
	const size_t	length_s1 = ft_strlen(s1);
	const size_t	length_s2 = ft_strlen(s2);
	size_t			index;
	size_t			index2;

	result = (char *)malloc((length_s1 + length_s2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	index2 = 0;
	while (s1 && s1[index2])
		result[index++] = s1[index2++];
	index2 = 0;
	while (s2 && s2[index2])
		result[index++] = s2[index2++];
	free(s1);
	result[length_s1 + length_s2] = '\0';
	return (result);
}
