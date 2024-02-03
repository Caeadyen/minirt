/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addobject.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:15:38 by hrings            #+#    #+#             */
/*   Updated: 2024/02/03 15:29:03 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_object *parseplane(t_minirt *minirt, char *line);
static t_object *parsespare(t_minirt *minirt, char *line);
static t_object *parsecylinder(t_minirt *minirt, char *line);

void	addobj(t_minirt *minirt, char *line, enum e_obj_type type)
{
	t_object	*object;

	object = NULL;
	if (type == SPHERE)
		object = parsespare(minirt, line);
	else if (type == CYLINDER)
		object = parsecylinder(minirt, line);
	else if (type == PLANE)
		object = parseplane(minirt, line);
	if (object)
		lst_obj_push(minirt, object);
}

static t_object *parseplane(t_minirt *minirt, char *line)
{
	t_object	*object;
	int color;
	t_vector *direction;
	t_vector *position;
	char	**tmp;

	object = (t_object *)malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	tmp = ft_split(line + 3, ' ');
	if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] == 0 || tmp[3] != 0)
		minirt->error = PLANEERROR;
	else
	{
		position = parsevector(minirt, tmp[0], PLANEPOSITION);
		direction = parsevector(minirt, tmp[1], PLANEDIRECTION);
		color = parsecolor(minirt, tmp[2], PLANECOLOR);
		object->specs = make_plane(position, direction, color);
		object->type = PLANE;
	}
	ft_free(tmp);
	return (object);
}

static t_object *parsespare(t_minirt *minirt, char *line)
{
	t_object	*object;
	t_vector *position;
	double	dia;
	int	color;
	char	**tmp;

	object = (t_object *)malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	tmp = ft_split(line + 3, ' ');
	if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] == 0 || tmp[3] != 0)
		minirt->error = SPAREERROR;
	else
	{
		position = parsevector(minirt, tmp[0], SPAREPOSITION);
		dia = ft_strtof(minirt, tmp[1], SPARECOLOR);
		color = parsecolor(minirt, tmp[2], SPARECOLOR);
		object->specs = make_sphere(position, dia, color);
		object->type = SPHERE;
	}
	ft_free(tmp);
	return (object);	
}

static t_object *parsecylinder(t_minirt *minirt, char *line)
{
	t_object	*object;
	t_vector *position;
	t_vector *direction;
	t_info		info;
	char	**tmp;

	object = (t_object *)malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	tmp = ft_split(line + 3, ' ');
	if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] == 0)
		minirt->error = SPAREERROR;
	else if (tmp[3] == 0 || tmp[4] == 0 || tmp[5] != 0)
		minirt->error = SPAREERROR;
	else
	{
		position = parsevector(minirt, tmp[0], CYLINDERPOSITION);
		direction = parsevector(minirt, tmp[1], CYLINDERDIRECTION);
		// if (checknormalized(direction))
		// 	minirt->error = CYLINDERNORM;
		norm_vector(direction);
		info.dia = ft_strtof(minirt, tmp[2], CYLINDERDIA);
		info.height = ft_strtof(minirt, tmp[3], CYLINDERHEIGHT);
		info.color = parsecolor(minirt, tmp[4], CYLINDERCOLOR);
		object->specs = make_cylinder(position, direction, info);
		object->type = SPHERE;
	}
	ft_free(tmp);
	return (object);
}