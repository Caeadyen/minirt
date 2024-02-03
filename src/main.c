/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:00:09 by hrings            #+#    #+#             */
/*   Updated: 2024/02/03 15:08:12 by hrings           ###   ########.fr       */
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
		if (minirt->error)
			handelerror(minirt);
		minirt->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
		initminirt(minirt);
		initimg(minirt);
		drawing(minirt);
		mlx_loop_hook(minirt->mlx, key_press, minirt);
		mlx_loop(minirt->mlx);
		close_win(minirt);
	}
	else
		ft_putendl_fd("Wrong usage: ./minirt <configfile>", 2);
	return (0);
}

static void	close_win(t_minirt *minirt)
{
	clear_obj_lst(minirt);
	if (minirt->mlx)
	{
		if (minirt->img)
			mlx_delete_image(minirt->mlx, minirt->img);
		mlx_terminate(minirt->mlx);
	}
	if (minirt->up_vector)
		free(minirt->up_vector);
	if (minirt->camera)
	{
		if (minirt->camera->orientation)
			free(minirt->camera->orientation);
		if (minirt->camera->position)
			free(minirt->camera->position);
		free(minirt->camera);
	}
	if (minirt->amlight)
		free(minirt->amlight);
	if (minirt->light)
	{
		if (minirt->light->position)
			free(minirt->light->position);
		free(minirt->light);
	}
	free(minirt);
}

static void	initimg(t_minirt *minirt)
{
	int		width;
	int		height;

	width = minirt->width;
	height = minirt->height;
	minirt->img = mlx_new_image(minirt->mlx, width, height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}

static void	initminirt(t_minirt *minirt)
{
	minirt->height = HEIGHT;
	minirt->width = WIDTH;
	minirt->up_vector = (t_vector *)malloc(sizeof(t_vector));
	minirt->up_vector->x = 0;
	minirt->up_vector->y = 1;
	minirt->up_vector->z = 0;
}

