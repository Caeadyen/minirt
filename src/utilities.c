/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:17 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 17:07:12 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	key_press(void *param)
{
	t_minirt	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
}

double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	max_double(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	ft_free(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}
