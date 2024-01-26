/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:58:12 by hrings            #+#    #+#             */
/*   Updated: 2024/01/26 23:42:15 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void		init_ray(t_minirt *minirt);
static t_vector	*get_l_position(t_minirt *minirt);
static double	get_d(t_minirt *minirt);

void	drawing(t_minirt *minirt)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	init_ray(minirt);
	while (i < minirt->width)
	{
		while (j < minirt->height)
		{
			color = raytracing(minirt, i, j);
			mlx_put_pixel(minirt->img, i, j, color);
			j++;
		}
		j = 0;
		i++;
	}
	clean_up_ray(minirt);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}


static void	init_ray(t_minirt *minirt)
{
	t_ray		*ray;
	t_vector	tmp;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		exit(1);
	minirt->ray = ray;
	tmp = scalar_product(minirt->cammera->orientation, -1);
	ray->n = init_vector(tmp);
	norm_vector(ray->n);
	tmp = cross_vector(minirt->up_vector, ray->n);
	ray->u = init_vector(tmp);
	norm_vector(ray->u);
	tmp = cross_vector(ray->n, ray->u);
	ray->v = init_vector(tmp);
	ray->d = get_d(minirt);
	ray->l = get_l_position(minirt);
	ray->s = NULL;
	ray->direction = NULL;
}

static t_vector	*get_l_position(t_minirt *minirt)
{
	t_vector	*result;
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector	d;

	a = scalar_product(minirt->ray->n, minirt->ray->d);
	c = sub_vector(minirt->cammera->position, &a);
	a = scalar_product(minirt->ray->u, minirt->width / 2);
	b = scalar_product(minirt->ray->v, minirt->height / 2);
	d = sub_vector(&c, &a);
	result = init_vector(add_vector(&d, &b));
	return (result);
}

static double	get_d(t_minirt *minirt)
{
	double	result;

	result = minirt->width / (2 * tan(minirt->cammera->fov * (M_PI / 180) / 2));
	return (result);
}
