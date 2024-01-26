/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:06:15 by hrings            #+#    #+#             */
/*   Updated: 2021/11/16 23:46:33 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	void	*result;

	if (!nelem || !size)
	{
		nelem = 1;
		size = 1;
	}
	result = malloc(nelem * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nelem * size);
	return (result);
}
