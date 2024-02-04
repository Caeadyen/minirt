/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:58:03 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 21:18:04 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	checkfileext(t_minirt *minirt);
static void	openfile(t_minirt *minirt);
static void	readfile(t_minirt *minirt);

void	readinput(t_minirt *minirt)
{
	checkfileext(minirt);
	if (!minirt->error)
		openfile(minirt);
	if (!minirt->error)
		readfile(minirt);
}

static void	checkfileext(t_minirt *minirt)
{
	int	len;

	len = ft_strlen(minirt->filename);
	if (len < 3)
		minirt->error = WRONGEXT;
	else if (ft_strncmp(minirt->filename + len - 3, ".rt", 3))
		minirt->error = WRONGEXT;
}

static void	openfile(t_minirt *minirt)
{
	minirt->fd = open(minirt->filename, O_RDONLY);
	if (minirt->fd == -1)
		minirt->error = FILENOTFOUND;
}

static void	readfile(t_minirt *minirt)
{
	char	*line;
	char	*tmp;

	line = get_next_line(minirt->fd);
	while (line)
	{
		tmp = ft_strtrim(line, " \n");
		free(line);
		if (!ft_strncmp(tmp, "A ", 2))
			addamlight(minirt, tmp);
		else if (!ft_strncmp(tmp, "C ", 2))
			addcamera(minirt, tmp);
		else if (!ft_strncmp(tmp, "L ", 2))
			addlight(minirt, tmp);
		else if (!ft_strncmp(tmp, "pl ", 3))
			addobj(minirt, tmp, PLANE);
		else if (!ft_strncmp(tmp, "sp ", 3))
			addobj(minirt, tmp, SPHERE);
		else if (!ft_strncmp(tmp, "cy ", 3))
			addobj(minirt, tmp, CYLINDER);
		else if (ft_strlen(tmp))
			minirt->error = PARSINGERROR;
		free(tmp);
		if (minirt->error)
			break ;
		line = get_next_line(minirt->fd);
	}
}
