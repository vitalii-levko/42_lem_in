/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:28:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:28:06 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	move_it_move_parent(t_tree **parent, t_step *steps, long long int w)
{
	long long int	sw;

	while (*parent && (*parent)->node->weight != w - 1)
	{
		sw = 0;
		steps = (*parent)->steps;
		while (steps)
		{
			if (steps->unit->node->ant == 0)
			{
				if (steps->unit->steps)
				{
					*parent = steps->unit->steps->unit->parent;
					sw = 1;
					break ;
				}
			}
			steps = steps->next;
		}
		if (sw == 0)
		{
			(*parent)->node->ant = 1;
			*parent = (*parent)->parent;
		}
	}
}

static void	move_it(t_tree **unit, t_node *node, long long int w)
{
	t_step			*steps;
	t_tree			*parent;

	parent = (*unit)->parent;
	while (parent)
	{
		steps = parent->steps;
		while (steps)
		{
			if (steps->unit->node == node)
			{
				*unit = steps->unit;
				return ;
			}
			steps = steps->next;
		}
		parent->node->ant = 1;
		parent = parent->parent;
		move_it_move_parent(&parent, NULL, w);
	}
}

void		try_move_it(t_tree **unit, t_list **queue, t_node **farm)
{
	move_it(unit, (*queue)->node, (*queue)->node->weight);
	reset_it(farm);
}

static void	move_it_move_it(t_tree **unit, t_node *node, long long int w)
{
	t_step			*steps;
	t_tree			*parent;

	if ((*unit)->steps && (*unit)->steps->unit->node == node)
	{
		*unit = (*unit)->steps->unit;
		return ;
	}
	parent = (*unit)->parent;
	while (parent)
	{
		steps = parent->steps;
		while (steps)
		{
			if (steps->unit->steps && steps->unit->steps->unit->node == node)
			{
				*unit = steps->unit->steps->unit;
				return ;
			}
			steps = steps->next;
		}
		parent->node->ant = 1;
		parent = parent->parent;
		move_it_move_parent(&parent, NULL, w);
	}
}

void		try_move_it_move_it(t_tree **unit, t_list **queue, t_node **farm)
{
	move_it_move_it(unit, (*queue)->node, (*unit)->node->weight);
	reset_it(farm);
	(*farm)->count = ((*queue)->node->weight);
}
