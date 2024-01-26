/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:59:57 by hrings            #+#    #+#             */
/*   Updated: 2021/11/24 10:46:08 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s, char const *set)
{
	char			*result;
	unsigned int	start;
	unsigned int	end;
	size_t			size;

	if (!s)
		return (NULL);
	if (!set || !*s)
		return (ft_strdup(s));
	start = 0;
	while (is_in_set(*(s + start), set) && *(s + start))
		start++;
	end = ft_strlen(s) - 1;
	if (start > end)
		return (ft_strdup(""));
	while (is_in_set(*(s + end), set) && end > start)
		end--;
	size = (size_t) end - start + 1;
	result = ft_substr(s, start, size);
	if (!result)
		return (NULL);
	return (result);
}

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
