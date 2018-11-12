/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_ext_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:44:15 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:44:16 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			mark_top(t_node **res, t_tree **path)
{
	t_node		*curr;
	t_list		*rooms;

	(*path)->node->top = 1;
	curr = *res;
	while (curr)
	{
		if (curr->id == (*path)->node->id)
			curr->top = 1;
		else
		{
			rooms = curr->rooms;
			while (rooms)
			{
				if (rooms->node->id == (*path)->node->id)
					rooms->node->top = 1;
				rooms = rooms->next;
			}
		}
		curr = curr->next;
	}
}

static t_node	*set_new_path(t_node **farm, long long int node_id)
{
	t_node		*curr;

	curr = *farm;
	while (curr)
	{
		if (curr->id == node_id)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_tree			*get_new_start(t_node **farm, t_tree **path, t_list **q, \
				t_node **res)
{
	t_node		*curr;
	t_list		*rooms;

	curr = *res;
	while (curr)
	{
		rooms = curr->rooms;
		while (rooms && rooms->next && !rooms->next->node->end)
		{
			if (!rooms->node->top && rooms->node->end == 0)
			{
				(*path)->node = set_new_path(farm, rooms->node->id);
				del_path(path);
				del_queue(q);
				push_queue(q, &(*path)->node, farm);
				return (*path);
			}
			rooms = rooms->next;
		}
		curr = curr->next;
	}
	del_queue(q);
	return (NULL);
}

t_tree			*move_start(t_tree **path, t_list **queue, t_node **res, \
				t_node **farm)
{
	t_step		*curr;

	if ((*path)->steps)
	{
		curr = (*path)->steps;
		while (curr)
		{
			if (!curr->unit->node->res && !curr->unit->node->top)
			{
				del_path(path);
				del_queue(queue);
				push_queue(queue, &(*path)->node, farm);
				return (*path);
			}
			curr = curr->next;
		}
	}
	(*path)->node->res = 1;
	mark_top(res, path);
	return (get_new_start(farm, path, queue, res));
}
