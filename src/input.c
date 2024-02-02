/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:58:03 by hrings            #+#    #+#             */
/*   Updated: 2024/02/01 11:45:34 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void checkfileext(t_minirt *minirt);
static void openfile(t_minirt *minirt);
static void readfile(t_minirt *minirt);
static void addamlight(t_minirt *minirt, char *line);
static void addcamera(t_minirt *minirt, char *line);
static void addlight(t_minirt *minirt, char *line);
// static void addobj(t_minirt *minirt, char *line, enum e_obj_type type);

void	readinput(t_minirt *minirt)
{
	checkfileext(minirt);
	if (!minirt->error)
		openfile(minirt);
	if (!minirt->error)
		readfile(minirt);
}

static void checkfileext(t_minirt *minirt)
{
	int	len;

	len = ft_strlen(minirt->filename);
	if (len < 3)
		minirt->error = WRONGEXT;
	else if (ft_strncmp(minirt->filename + len - 3, ".rt", 3))
		minirt->error = WRONGEXT;
		
}
static void openfile(t_minirt *minirt)
{
	minirt->fd = open(minirt->filename, O_RDONLY);
	if (minirt->fd == -1)
		minirt->error = FILENOTFOUND;
}

static void readfile(t_minirt *minirt)
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
		// if (ft_strncmp(line, "A ", 2))
		// 	addamlight(minirt, line);
		else
			ft_putstr_fd("empty line\n",1);
		free(tmp);
		if (minirt->error)
			break ;
		line = get_next_line(minirt->fd);
	}
	// minirt->error = PARSINGERROR;
}

static void addamlight(t_minirt *minirt, char *line)
{
	char **tmp;

	ft_putstr_fd("am light found\n",1);
	tmp = ft_split(line + 2, ' ');
	//ft_putstr_fd(tmp[1],1);
	if (tmp[2] != 0)
		minirt->error = AMLIGHTFORMAT;
	else
	{
		
	
	while (*tmp)
	{
		ft_putstr_fd(*tmp,1);
		ft_putstr_fd("\n",1);
		free(*tmp);
		tmp++;
		
	}
	}

	ft_putstr_fd("\n",1);
	//minirt->error = PARSINGERROR;
}
static void addcamera(t_minirt *minirt, char *line)
{
	ft_putstr_fd("camera found\n",1);
	ft_putstr_fd(line,1);
	ft_putstr_fd("\n",1);
	minirt->error = PARSINGERROR;
}
static void addlight(t_minirt *minirt, char *line)
{
	ft_putstr_fd("light found\n",1);
	ft_putstr_fd(line,1);
	ft_putstr_fd("\n",1);
	minirt->error = PARSINGERROR;
}


// static void	addobj(t_minirt *minirt, char *line, enum e_obj_type type)
// {
// 	t_vector	position;
// 	t_vector	direction;
// 	t_object	*object;
// 	t_info		info;
// 	double		dia;
// 	int			color;
// 	if (type == SPHERE)
// 	{
// 	object = (t_object *)malloc(sizeof(t_object));
// 	if (!object)
// 		exit(1);
// 	position.x = 0;
// 	position.y = 0;
// 	position.z = 0;
// 	dia = 30;
// 	color = 255 << 8;
// 	object->specs = make_sphere(position, dia, color);
// 	object->type = SPHERE;
// 	lst_obj_push(minirt, object);
// 	}
// 	else if (type == CYLINDER)
// 	{
// 	object = (t_object *)malloc(sizeof(t_object));
// 	if (!object)
// 		exit(1);
// 	position.x = 0;
// 	position.y = 0;
// 	position.z = 0;
// 	direction.x = 0;
// 	direction.y = 0;
// 	direction.z = 1;
// 	norm_vector(&direction);
// 	info.dia = 20;
// 	info.color = 255 << 16;
// 	info.height = 100;
// 	object->specs = make_cylinder(position, direction, info);
// 	object->type = CYLINDER;
// 	lst_obj_push(minirt, object);
// 	}
// 	else if (type == PLANE)
// 	{
// 	object = (t_object *)malloc(sizeof(t_object));
// 	if (!object)
// 		exit(1);
// 	color = 255 << 16;
// 	direction.x = -1;
// 	direction.y = 0;
// 	direction.z = 0;
// 	position.x = 20;
// 	position.y = 0;
// 	position.z = 0;	
// 	object->specs = make_plane(position, direction, color);
// 	object->type = PLANE;
// 	lst_obj_push(minirt, object);
// 	}
// }
