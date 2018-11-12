/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dels.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:02:25 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:02:29 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		del_queue(t_list **queue)
{
	t_list		*curr;

	while (*queue)
	{
		curr = *queue;
		*queue = (*queue)->next;
		free(curr);
		curr = NULL;
	}
}

void		del_farm(t_node **farm)
{
	t_node		*curr;
	t_node		*next;
	t_list		*rooms;
	t_list		*prev;

	curr = (farm) ? *farm : NULL;
	while (curr)
	{
		rooms = curr->rooms;
		while (rooms)
		{
			prev = rooms;
			rooms = rooms->next;
			free(prev);
			prev = NULL;
		}
		next = curr->next;
		ft_strdel(&curr->name);
		curr->name = NULL;
		free(curr);
		curr = next;
	}
	if (farm)
		*farm = NULL;
}

void		del_map(t_map **map)
{
	t_map		*curr;

	while (*map)
	{
		curr = *map;
		*map = (*map)->next;
		ft_strdel(&curr->str);
		free(curr);
		curr = NULL;
	}
}

static void	del_res_node(t_list **room)
{
	ft_strdel(&(*room)->node->name);
	free((*room)->node);
	(*room)->node = NULL;
}

void		del_res(t_node **res)
{
	t_node		*curr;
	t_node		*next;
	t_list		*rooms;
	t_list		*prev;

	curr = (res) ? *res : NULL;
	while (curr)
	{
		rooms = curr->rooms;
		while (rooms)
		{
			prev = rooms;
			rooms = rooms->next;
			del_res_node(&prev);
			free(prev);
			prev = NULL;
		}
		next = curr->next;
		ft_strdel(&curr->name);
		curr->name = NULL;
		free(curr);
		curr = next;
	}
	if (res)
		*res = NULL;
}
