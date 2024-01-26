/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:08:56 by hrings            #+#    #+#             */
/*   Updated: 2021/11/17 22:51:48 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_number_words(char const *s, char c);
static void		add_word(char const *s, char c, size_t n_words, char **result);

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	n_words;

	if (!s)
		return (NULL);
	if (!*s)
	{
		result = (char **)malloc(1 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	n_words = find_number_words(s, c);
	result = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	add_word(s, c, n_words, result);
	return (result);
}

static void	add_word(char const *s, char c, size_t n_words, char **result)
{
	size_t	size_word;
	size_t	index;
	size_t	index_2;

	index = 0;
	index_2 = 0;
	while (index_2 < n_words && *s)
	{
		while (s[index] == c && s[index] != '\0')
			index++;
		size_word = 0;
		while (s[index + size_word] != c && s[index + size_word] != '\0')
			size_word++;
		result[index_2++] = ft_substr(s + index, 0, size_word);
		index += size_word;
	}
	result[index_2] = 0;
}

static size_t	find_number_words(char const *s, char c)
{
	size_t	result;

	result = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		result++;
		while (*s != c && *s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
	}
	return (result);
}
