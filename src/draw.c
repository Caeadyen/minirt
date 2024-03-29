/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:58:12 by hrings            #+#    #+#             */
/*   Updated: 2024/02/06 16:10:06 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vector	init_ray_dir(t_minirt *minirt, t_luv *luv, int x, int y);
static t_luv	generateluv(t_minirt *minirt);

void	drawing(t_minirt *minirt)
{
	int		i;
	int		j;
	int		sample;
	t_color	color;
	t_ray	ray;
	t_luv	luv;

	i = 0;
	j = 0;
	luv = generateluv(minirt);
	ray.pos = scalar_product(minirt->camera->position, 1);
	while (i < minirt->width)
	{
		while (j < minirt->height)
		{
			color = initcolor();
			sample = 0;
			while (sample < SAMPLESIZE)
			{
				ray.direction = init_ray_dir(minirt, &luv, j, i);
				addcolor(&color, raytracing(minirt, &ray, MAXRAYDEPTH));
				++sample;
			}
			averagecolor(&color, SAMPLESIZE);
			mlx_put_pixel(minirt->img, i, j, decodecolor(&color));
			j++;
		}
		j = 0;
		i++;
	}
	printf("done drawing ...\n");
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}

static t_vector	init_ray_dir(t_minirt *minirt, t_luv *luv, int row, int col)
{
	t_vector	direction;
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector	s;

	a = scalar_product(&luv->u, (double) col + -0.5 + random_double());
	b = scalar_product(&luv->v, (double) row + -0.5 + random_double());
	c = sub_vector(&a, &b);
	s = add_vector(&luv->l, &c);
	direction = sub_vector(&s, minirt->camera->position);
	norm_vector(&direction);
	return (direction);
}

static t_luv	generateluv(t_minirt *minirt)
{
	t_luv		luv;
	t_vector	normal;
	double		distance;
	t_vector	a;
	t_vector	b;

	normal = scalar_product(minirt->camera->orientation, -1);
	norm_vector(&normal);
	luv.u = cross_vector(minirt->up_vector, &normal);
	norm_vector(&luv.u);
	luv.v = cross_vector(&normal, &luv.u);
	distance = minirt->width / (2 * tan(minirt->camera->fov * (M_PI / 180) / 2));
	b = pointonline(minirt->camera->position, minirt->camera->orientation, distance);
	a = scalar_product(&luv.u, minirt->width / 2);
	luv.l = sub_vector(&b, &a);
	a = scalar_product(&luv.v, minirt->height / 2);
	luv.l = add_vector(&luv.l, &a);
	return (luv);
}
