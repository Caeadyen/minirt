/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:56:39 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 19:46:47 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <stdio.h>
# include <libft.h>
# include <math.h>
# include <fcntl.h>
# include "keys.h"
# include "error.h"
# define TITLE "Minirt Project"

#define WIDTH 1200
#define HEIGHT 800

enum e_obj_type
{
	NONE,
	SPHERE,
	CYLINDER,
	PLANE,
	LIGHT
};

enum e_hit_typ
{
	NO,
	TOP,
	BASE,
	MANTLE,
	INSIDE,
	OUTSIDE
};

typedef struct s_info
{
	double dia;
	double height;
	int color;
}	t_info;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_abc
{
	double	a;
	double	b;
	double	c;
}	t_abc;

typedef struct s_camera
{
	t_vector	*position;
	t_vector	*orientation;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	*position;
	int	color;
	double		brightness;
}	t_light;

typedef struct s_amlight
{
	int	color;
	double		ratio;
}	t_amlight;

typedef struct s_lst_obj
{
	void				*obj;
	struct s_lst_obj	*next;
}	t_lst_obj;


typedef struct s_sphere
{
	t_vector	*position;
	double		diameter;
	int			color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	*position;
	t_vector	*direction;
	double		diameter;
	double		height;
	int			color;
	t_vector	*top;
	t_vector	*base;
	t_vector	*axis;
}	t_cylinder;

typedef struct s_plane
{
	t_vector	*position;
	t_vector	*normal;
	int			color;
}	t_plane;

typedef struct s_object
{
	int		type;
	void	*specs;
}	t_object;

typedef struct s_hit
{
	t_object	*hit;
	double		distance;
	int			type;
	int			where;
}	t_hit;

typedef struct s_ray
{
	t_vector	*n;
	t_vector	*u;
	t_vector	*v;
	t_vector	*l;
	t_vector	*s;
	t_vector	*direction;
	double		d;
	
} t_ray;

typedef struct s_minirt
{
	char		*filename;
	int			fd;
	int			error;
	int			height;
	int			width;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_vector	*up_vector;
	t_lst_obj	*objects;
	t_camera	*camera;
	t_light		*light;
	t_ray		*ray;
	t_amlight	*amlight;
}	t_minirt;

//draw.c
void	drawing(t_minirt *minirt);
//raytracing.c
int		raytracing(t_minirt *minirt, int row, int col);
t_hit check_sphere_hit(t_minirt *minirt, t_object *obj);
//cleanup.c
void	cleanup(t_object *object);
void	clean_up_ray(t_minirt *minirt);
//lst_obj.c
void	lst_obj_push(t_minirt *minirt, t_object *obj);
void	clear_obj_lst(t_minirt *minirt);
//utilities.c
void		key_press(void* param);
double min_double(double a, double b);
double max_double(double a, double b);
void	ft_free(char **array);
//vector_3d.c
t_vector *init_vector(t_vector a);
t_vector cross_vector(t_vector *a, t_vector *b);
void	norm_vector(t_vector *a);
t_vector scalar_product(t_vector *a, double num);
double dot_product(t_vector *a, t_vector *b);
t_vector add_vector(t_vector *a, t_vector *b);
t_vector sub_vector(t_vector *a, t_vector *b);
void assign_vec(t_vector *a, t_vector b);
t_vector	ray_point(t_vector *start, t_vector *dir, double t);
bool	checknormalized(t_vector *v);

//make_obj
t_sphere *make_sphere(t_vector position, double dia, int color);
t_cylinder *make_cylinder(t_vector position, t_vector direction, t_info info);
t_plane *make_plane(t_vector position, t_vector normal, int color);
//color.c
int	get_a(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);
int get_rgba(int r, int g, int b, int a);
//cylinder.c
t_hit check_cylinder_hit(t_minirt *minirt, t_object *obj);
void cal_ino_cylinder(t_cylinder *cylinder);
//plane.c
t_hit check_plane_hit(t_minirt *minirt, t_object *obj);
//input.c
void	readinput(t_minirt *minirt);
//error.c
void handelerror(t_minirt *minirt);
//addelement.c
void	addamlight(t_minirt *minirt, char *line);
void	addcamera(t_minirt *minirt, char *line);
void	addlight(t_minirt *minirt, char *line);
//parser.c
double ft_strtof(t_minirt *minirt, char *str, int error);
bool	checkdrange(double value, double min, double max);
bool	checkirange(int value, int min, int max);
int	parsecolor(t_minirt *minirt, char *str, int error);
t_vector *parsevector(t_minirt *minirt, char *str, int error);

#endif
