/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addelement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:26:30 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 19:48:11 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	addamlight(t_minirt *minirt, char *line)
{
	char	**tmp;
	t_amlight *amlight;

	if (!minirt->amlight)
	{
		amlight = (t_amlight *)malloc(sizeof(t_camera));
		if (!amlight)
			exit(1);
		tmp = ft_split(line + 2, ' ');
		if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] != 0)
			minirt->error = AMLIGHTFORMAT;
		else
		{
			amlight->ratio = ft_strtof(minirt, tmp[0], AMLIGHTRATIO);
			if (checkdrange(amlight->ratio, 0, 1))
				minirt->error = AMLIGHTRANGE;
			amlight->color = parsecolor(minirt, tmp[1], AMLIGHTCOLOR);		
		}
		minirt->amlight = amlight;
		ft_free(tmp);
	}
	else
		minirt->error = AMLIGHTMULTI;
}

void	addcamera(t_minirt *minirt, char *line)
{
	char	**tmp;
	t_camera	*cam;

	if (!minirt->camera)
	{
		tmp = ft_split(line + 2, ' ');
		if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] == 0 || tmp[3] != 0)
			minirt->error = AMLIGHTFORMAT;
		else
		{
			cam = (t_camera *)malloc(sizeof(t_camera));
			if (!cam)
				exit(1);
			cam->position = parsevector(minirt, tmp[0], CAMPOSITION);
			cam->orientation = parsevector(minirt, tmp[1], CAMORITATION);
			if (checknormalized(cam->orientation))
				minirt->error = CAMORNORM;
			cam->fov = ft_strtof(minirt, tmp[2], CAMFOV);
			if (checkdrange(cam->fov, 0, 180))
				minirt->error = CAMFOVRANGE;
			minirt->camera = cam;
		}
		ft_free(tmp);
	}
	else
		minirt->error = CAMMULTI;
}

void	addlight(t_minirt *minirt, char *line)
{
	ft_putstr_fd("light found\n", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\n", 1);
	minirt->error = PARSINGERROR;
}
