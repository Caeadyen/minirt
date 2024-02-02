/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addelement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:26:30 by hrings            #+#    #+#             */
/*   Updated: 2024/02/02 16:55:46 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	addamlight(t_minirt *minirt, char *line)
{
	char	**tmp;

	if (!minirt->iamlight)
	{
		minirt->iamlight = true;
		ft_putstr_fd("am light found\n", 1);
		tmp = ft_split(line + 2, ' ');
		if (tmp == 0 || tmp[0] == 0 || tmp[1] == 0 || tmp[2] != 0)
			minirt->error = AMLIGHTFORMAT;
		else
		{
			minirt->amlight = ft_strtof(minirt, tmp[0], AMLIGHTRATIO);
			if (checkdrange(minirt->amlight, 0, 1))
				minirt->error = AMLIGHTRANGE;
			printf("Am light ratio: %f\n", minirt->amlight);
		}
		ft_free(tmp);
	}
	else
		minirt->error = AMLIGHTMULTI;
}

void	addcamera(t_minirt *minirt, char *line)
{
	ft_putstr_fd("camera found\n", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\n", 1);
	minirt->error = PARSINGERROR;
}

void	addlight(t_minirt *minirt, char *line)
{
	ft_putstr_fd("light found\n", 1);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\n", 1);
	minirt->error = PARSINGERROR;
}
