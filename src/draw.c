/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:58:12 by hrings            #+#    #+#             */
/*   Updated: 2024/02/04 21:02:21 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_ray	init_ray(t_minirt *minirt, int x, int y);
static t_vector	get_l_position(t_minirt *minirt, t_ray *ray);
static double	get_d(t_minirt *minirt);
static void		get_s_and_dir(t_minirt *minirt, t_ray *ray, int row, int col);

void	drawing(t_minirt *minirt)
{
	int		i;
	int		j;
	int		color;
	t_ray	ray;

	i = 0;
	j = 0;
	while (i < minirt->width)
	{
		while (j < minirt->height)
		{
			ray = init_ray(minirt, j, i);
			color = raytracing(minirt, &ray);
			mlx_put_pixel(minirt->img, i, j, color);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}

static t_ray	init_ray(t_minirt *minirt, int x, int y)
{
	t_ray		ray;

	ray.n = scalar_product(minirt->camera->orientation, -1);
	norm_vector(&ray.n);
	ray.u = cross_vector(minirt->up_vector, &ray.n);
	norm_vector(&ray.u);
	ray.v = cross_vector(&ray.n, &ray.u);
	ray.d = get_d(minirt);
	ray.l = get_l_position(minirt, &ray);
	get_s_and_dir(minirt, &ray, x, y);
	ray.pos = scalar_product(minirt->camera->position, 1);
	return (ray);
}

static t_vector	get_l_position(t_minirt *minirt, t_ray *ray)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector	d;

	a = scalar_product(&ray->n, ray->d);
	c = sub_vector(minirt->camera->position, &a);
	a = scalar_product(&ray->u, minirt->width / 2);
	b = scalar_product(&ray->v, minirt->height / 2);
	d = sub_vector(&c, &a);
	return (add_vector(&d, &b));
}

static double	get_d(t_minirt *minirt)
{
	double	result;

	result = minirt->width / (2 * tan(minirt->camera->fov * (M_PI / 180) / 2));
	return (result);
}

static void	get_s_and_dir(t_minirt *minirt, t_ray *ray, int row, int col)
{
	t_vector	a;
	t_vector	b;
	t_vector	c;

	a = scalar_product(&ray->u, col);
	b = scalar_product(&ray->v, row);
	c = sub_vector(&a, &b);
	a = add_vector(&ray->l, &c);
	ray->s = add_vector(&ray->l, &c);
	ray->direction = sub_vector(&ray->s, minirt->camera->position);
	norm_vector(&ray->direction);
}
