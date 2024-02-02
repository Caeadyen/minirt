/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:00:09 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 19:49:24 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	initimg(t_minirt *minirt);
static void	initminirt(t_minirt *minirt);
static void	close_win(t_minirt *minirt);

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	if (argc == 2)
	{
		minirt = (t_minirt *)ft_calloc(1, sizeof(t_minirt));
		if (!minirt)
			return (1);
		minirt->filename = argv[1];
		readinput(minirt);
		ft_putnbr_fd(minirt->error, 1);
		if (minirt->error)
			handelerror(minirt);
		minirt->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
		initminirt(minirt);
		initimg(minirt);
		drawing(minirt);
		mlx_loop_hook(minirt->mlx, key_press, minirt);
		mlx_loop(minirt->mlx);
		mlx_delete_image(minirt->mlx, minirt->img);
		mlx_terminate(minirt->mlx);
		close_win(minirt);
	}
	else
		ft_putendl_fd("Wrong usage: ./minirt <configfile>", 2);
	return (0);
}

static void	close_win(t_minirt *minirt)
{
	clear_obj_lst(minirt);
	free(minirt->up_vector);
	free(minirt->camera->orientation);
	free(minirt->camera->position);
	free(minirt->camera);
	if (minirt->amlight)
		free(minirt->amlight);
	free(minirt);
}

// static void	addobj(t_minirt *minirt)
// {
// 	t_vector	position;
// 	t_vector	direction;
// 	t_object	*object;
// 	t_object	*object2;
// 	t_object	*object3;
// 	t_info		info;
// 	double		dia;
// 	int			color;
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
// 	object2 = (t_object *)malloc(sizeof(t_object));
// 	if (!object2)
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
// 	object2->specs = make_cylinder(position, direction, info);
// 	object2->type = CYLINDER;
// 	lst_obj_push(minirt, object2);
// 	object3 = (t_object *)malloc(sizeof(t_object));
// 	if (!object3)
// 		exit(1);
// 	color = 255 << 16;
// 	direction.x = -1;
// 	direction.y = 0;
// 	direction.z = 0;
// 	position.x = 20;
// 	position.y = 0;
// 	position.z = 0;	
// 	object3->specs = make_plane(position, direction, color);
// 	object3->type = PLANE;
// 	lst_obj_push(minirt, object3);
// }

static void	initimg(t_minirt *minirt)
{
	int		width;
	int		height;

	width = minirt->width;
	height = minirt->height;
	minirt->img = mlx_new_image(minirt->mlx, width, height);
}

static void	initminirt(t_minirt *minirt)
{
	minirt->height = 800;
	minirt->width = 1200;
	minirt->objects = NULL;
	minirt->up_vector = (t_vector *)malloc(sizeof(t_vector));
	minirt->up_vector->x = 0;
	minirt->up_vector->y = 0;
	minirt->up_vector->z = 1;
}

// static void	addcam(t_minirt *minirt)
// {
// 	t_camera	*cam;
// 	t_vector	*position;
// 	t_vector	*oritantion;

// 	cam = (t_camera *)malloc(sizeof(t_camera));
// 	if (!cam)
// 		exit(1);
// 	oritantion = (t_vector *)malloc(sizeof(t_vector));
// 	if (!oritantion)
// 		exit(1);
// 	position = (t_vector *)malloc(sizeof(t_vector));
// 	if (!position)
// 		exit(1);
// 	position->x = -100;
// 	position->y = 0;
// 	position->z = 0;
// 	oritantion->x = 1;
// 	oritantion->y = 0;
// 	oritantion->z = 0;
// 	cam->position = position;
// 	cam->orientation = oritantion;
// 	cam->fov = 90;
// 	minirt->camera = cam;
// }
