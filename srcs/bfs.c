/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:21:00 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:21:02 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_node	*get_start(t_node **farm)
{
	t_node		*curr;

	curr = *farm;
	while (curr)
	{
		if (curr->start)
			return (curr);
		curr = curr->next;
	}
	p_err(1, "'start' room did not found", NULL, farm);
	return (NULL);
}

static void		bfs_queue(t_list **queue, t_node **farm, t_tree **unit)
{
	if ((*farm)->count < (*queue)->node->weight)
		try_move_it_move_it(unit, queue, farm);
	else
		try_move_it(unit, queue, farm);
}

static void		reset_res(t_node **res, t_node *curr, t_node *head, \
							t_list *rooms)
{
	while (curr)
	{
		rooms = curr->rooms;
		while (rooms)
		{
			rooms->node->top = 0;
			head = *res;
			while (head)
			{
				if (head->id == rooms->node->id)
					rooms->node->top = 1;
				head = head->next;
			}
			rooms->node->visited = 0;
			rooms->node->res = 0;
			rooms->node->x = 0;
			rooms->node->y = 0;
			rooms = rooms->next;
		}
		curr->visited = 0;
		curr->res = 0;
		curr->x = 0;
		curr->y = 0;
		curr = curr->next;
	}
}

static int		bfs_ret(t_node **res, long long int total, t_node **farm)
{
	if (*res == NULL && total > 0)
		return (p_err(1, "No possible path found", NULL, farm));
	reset_res(res, *res, NULL, NULL);
	return (0);
}

int				bfs(t_node **farm, t_tree **path, t_node **res, t_list *queue)
{
	t_node			*curr;
	t_tree			*unit;

	if (!(curr = get_start(farm)))
		return (1);
	*path = create_unit(&curr, NULL);
	unit = *path;
	push_queue(&queue, &curr, farm);
	while (queue)
	{
		if (visit_queue(farm, &queue, &unit, res))
		{
			unit = move_start(path, &queue, res, farm);
			continue;
		}
		if (queue)
			bfs_queue(&queue, farm, &unit);
		else
		{
			mark_top(res, path);
			(*farm)->count = 0;
			unit = get_new_start(farm, path, &queue, res);
		}
	}
	return (bfs_ret(res, (*farm)->total, farm));
}
