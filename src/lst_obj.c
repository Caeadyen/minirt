/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:19:27 by hrings            #+#    #+#             */
/*   Updated: 2022/11/16 20:53:30 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_lst_obj	*lst_obj_new(t_object *obj);
//static void			clean_up_obj(t_object *obj);

void	lst_obj_push(t_minirt *minirt, t_object *obj)
{
	t_lst_obj	*current;

	if (!minirt->objects)
		minirt->objects = lst_obj_new(obj);
	else
	{
		current = minirt->objects;
		while (current->next)
			current = current->next;
		current->next = lst_obj_new(obj);
	}
}

void	clear_obj_lst(t_minirt *minirt)
{
	t_lst_obj	*current;
	t_lst_obj	*next;

	next = minirt->objects;
	while (next)
	{
		current = next;
		next = next->next;
		cleanup(current->obj);
		free(current);
	}
	minirt->objects = NULL;
}

static t_lst_obj	*lst_obj_new(t_object *obj)
{
	t_lst_obj	*new_lst;

	new_lst = (t_lst_obj *)malloc(sizeof(t_lst_obj));
	if (!new_lst)
		return (NULL);
	new_lst->obj = obj;
	new_lst->next = NULL;
	return (new_lst);
}
