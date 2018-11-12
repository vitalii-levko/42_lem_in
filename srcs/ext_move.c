/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:13:13 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:13:15 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static long long int	move_get_first(t_node **curr, t_list **rooms)
{
	long long int	x;

	x = (*curr)->x;
	while ((*rooms)->node->ant == 0 || (*rooms)->node->visited)
	{
		if ((*rooms)->node->visited)
			x -= 1;
		*rooms = (*rooms)->next;
	}
	return (x);
}

static void				move_get_last(t_list **inner, long long int i, \
						long long int *j, long long int *x)
{
	while (i > *j)
	{
		*inner = (*inner)->next;
		if ((*inner)->node->ant != 0 || (*inner)->node->visited)
		{
			i--;
			if ((*inner)->node->visited)
				*x -= 1;
		}
	}
}

static void				move_last_end(t_node **res, t_node **curr, \
						t_list **inner)
{
	(*inner)->node->ant = 0;
	(*res)->res += 1;
	(*curr)->x -= 1;
}

static void				move_further(t_act **act, t_list **inner, t_node **farm)
{
	insert_act(act, (*inner)->node->ant, (*inner)->next->node->name, farm);
	(*inner)->next->node->ant = (*inner)->node->ant;
	(*inner)->node->ant = 0;
}

void					try_move_path(t_node **res, t_node **curr, \
						t_act **act, t_node **farm)
{
	t_list			*inner;
	long long int	ij[2];
	long long int	x;
	t_list			*rooms;

	rooms = (*curr)->rooms;
	ij[1] = 1;
	x = move_get_first(curr, &rooms);
	while (rooms->node->ant)
	{
		inner = rooms;
		ij[0] = x;
		move_get_last(&inner, ij[0], &ij[1], &x);
		if (inner->next->node->end)
		{
			insert_act(act, inner->node->ant, inner->next->node->name, farm);
			move_last_end(res, curr, &inner);
		}
		else if (inner->node->top)
			inspect_top(res, inner, act, farm);
		else
			move_further(act, &inner, farm);
		ij[1] += 1;
	}
}
