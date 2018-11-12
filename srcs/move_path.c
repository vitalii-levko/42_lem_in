/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:10:30 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:10:31 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*get_parent(t_node **res, long long int id)
{
	t_node		*curr;
	t_list		*rooms;

	curr = *res;
	while (curr)
	{
		rooms = curr->rooms;
		while (rooms)
		{
			if (rooms->node->id == id)
				return (curr);
			rooms = rooms->next;
		}
		curr = curr->next;
	}
	return (*res);
}

void	inspect_top(t_node **res, t_list *inner, t_act **act, t_node **farm)
{
	t_node		*curr;
	t_node		*prev;

	curr = *res;
	while (curr->id != inner->node->id)
		curr = curr->next;
	prev = get_parent(res, curr->id);
	if (curr->count + curr->x < prev->count + prev->x - 1 \
	&& curr->rooms->node->ant == 0)
	{
		curr->visited = 1;
		curr->x += 1;
		prev->x -= 1;
		curr->rooms->node->ant = inner->node->ant;
		curr->rooms->node->visited = 1;
		inner->node->ant = 0;
		insert_act(act, curr->rooms->node->ant, curr->rooms->node->name, farm);
	}
	else
	{
		inner->next->node->ant = inner->node->ant;
		inner->node->ant = 0;
		insert_act(act, inner->next->node->ant, inner->next->node->name, farm);
	}
}

void	move_path(t_node **res, t_node *curr, t_act **act, t_node **farm)
{
	while (curr)
	{
		if ((curr->x && !curr->visited) || curr->x > 1)
			try_move_path(res, &curr, act, farm);
		curr = curr->next;
	}
}
