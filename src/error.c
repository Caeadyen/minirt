/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:49 by hrings            #+#    #+#             */
/*   Updated: 2024/02/01 11:17:24 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void printerror(int num);
static void freeupall(t_minirt *minirt);

void handelerror(t_minirt *minirt)
{
	int	error;

	error = minirt->error;
	printerror(minirt->error);
	freeupall(minirt);
	exit(error);
}

static void printerror(int num)
{
	if (num == WRONGEXT)
		ft_putstr_fd("Wrong file extension, need to be .rt\n", 2);
	
}

static void freeupall(t_minirt *minirt)
{
	if (minirt)
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
		free(minirt);
	}
}