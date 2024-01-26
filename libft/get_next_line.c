/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:57:43 by hrings            #+#    #+#             */
/*   Updated: 2022/02/03 10:45:35 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*line_save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_save = ft_read_file(fd, line_save);
	if (line_save == NULL)
	{
		return (line_save);
	}
	line = ft_find_line(line_save);
	line_save = remove_line(line_save);
	return (line);
}

char	*ft_read_file(int fd, char *line_save)
{
	char	*read_buff;
	int		read_byte;

	if (line_save && ft_strchr_gnl(line_save, '\n'))
		return (line_save);
	read_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buff)
		return (NULL);
	read_byte = 1;
	read_buff[0] = '\0';
	while (read_byte > 0 && !ft_strchr_gnl(read_buff, '\n'))
	{
		read_byte = read(fd, read_buff, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(read_buff);
			return (line_save);
		}
		read_buff[read_byte] = '\0';
		line_save = ft_strjoin_gnl(line_save, read_buff);
	}
	free(read_buff);
	return (line_save);
}

char	*ft_find_line(char *line_save)
{
	size_t	index;
	char	*result;

	if (!line_save || !*line_save)
		return (NULL);
	index = 0;
	while (line_save[index] && line_save[index] != '\n')
		index++;
	result = malloc(sizeof(char) * (index + 2));
	if (!result)
		return (NULL);
	index = 0;
	while (line_save[index] && line_save[index] != '\n')
	{
		result[index] = line_save[index];
		index++;
	}
	if (line_save[index] == '\n')
	{
		result[index] = line_save[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*remove_line(char *line_save)
{
	size_t	index;
	size_t	index2;
	char	*result;

	if (!line_save)
		return (NULL);
	index = 0;
	while (line_save[index] != '\n' && line_save[index] != '\0')
		index++;
	if (!line_save[index])
	{
		free(line_save);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(line_save) - index + 1));
	if (!result)
		return (NULL);
	index2 = 0;
	while (line_save[++index] != '\0')
	{
		result[index2++] = line_save[index];
	}
	result[index2] = '\0';
	free(line_save);
	return (result);
}

int	ft_strchr_gnl(char *s, char c)
{
	size_t	index;

	index = 0;
	while (*(s + index))
	{
		if (*(s + index) == c)
			return (1);
		index++;
	}
	return (0);
}
