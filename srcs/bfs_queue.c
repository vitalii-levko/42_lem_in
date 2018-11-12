/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:50:57 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:50:58 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	is_queued(t_list **queue, t_node *node)
{
	t_list		*curr;

	curr = *queue;
	while (curr)
	{
		if (curr->node == node)
			return (1);
		curr = curr->next;
	}
	return (0);
}

static int	inspect_node(t_list **queue, t_tree **unit, t_node **res, \
			t_node **farm)
{
	t_list *rooms;

	rooms = (*queue)->node->rooms;
	while (rooms)
	{
		if (!rooms->node->visited && !rooms->node->res \
			&& !is_queued(queue, rooms->node))
		{
			rooms->node->weight = (*queue)->node->weight + 1;
			if (rooms->node->end && !(*queue)->node->res)
			{
				end_point(unit, &rooms->node, res, farm);
				return (1);
			}
			append_step(unit, &rooms->node, farm);
			push_queue(queue, &rooms->node, farm);
		}
		rooms = rooms->next;
	}
	return (0);
}

static int	shift_queue(t_list **queue)
{
	t_list		*curr;

	curr = *queue;
	if (*queue)
	{
		*queue = (*queue)->next;
		free(curr);
		curr = NULL;
	}
	return (0);
}

static int	unset_visited_weight(t_node **farm, t_node *curr, t_list *rooms)
{
	while (curr)
	{
		if (curr->id != -1)
		{
			rooms = curr->rooms;
			while (rooms)
			{
				if (!rooms->node->res && rooms->node->visited)
				{
					rooms->node->visited = 0;
					rooms->node->weight = 0;
				}
				rooms = rooms->next;
			}
			if (!curr->res && curr->visited)
			{
				curr->visited = 0;
				curr->weight = 0;
			}
		}
		curr = curr->next;
	}
	(*farm)->count = 0;
	return (1);
}

int			visit_queue(t_node **farm, t_list **queue, t_tree **unit, \
			t_node **res)
{
	t_node		*curr;

	if (inspect_node(queue, unit, res, farm))
		return (unset_visited_weight(farm, *farm, NULL));
	curr = *farm;
	while (curr)
	{
		if (!curr->visited && !curr->res && is_paired(queue, curr->rooms))
		{
			curr->weight = (*queue)->node->weight + 1;
			if (curr->end && !(*queue)->node->res)
			{
				end_point(unit, &curr, res, farm);
				return (unset_visited_weight(farm, *farm, NULL));
			}
			else if (curr->end && (*queue)->node->res)
				return (shift_queue(queue));
			append_step(unit, &curr, farm);
			push_queue(queue, &curr, farm);
		}
		curr = curr->next;
	}
	return (shift_queue(queue));
}
