/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:03:21 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:03:23 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	move_it_inc(t_node **res, long long int *n, int x)
{
	*n += 1;
	if (x)
		(*res)->x += 1;
	else
		(*res)->res += 1;
}

static void	move_st_end(t_node **res, t_list **rooms, t_act **act, \
						t_node **farm)
{
	insert_act(act, (*farm)->count, (*rooms)->node->name, farm);
	move_it_inc(res, &(*farm)->count, 0);
}

static void	i_like_to_move_it(t_node **res, t_node *curr, t_act **act, \
								t_node **f)
{
	t_list		*rooms;

	rooms = curr->rooms;
	if (rooms->node->end)
		move_st_end(res, &rooms, act, f);
	else
	{
		rooms->node->ant = (*f)->count;
		insert_act(act, rooms->node->ant, rooms->node->name, f);
		move_it_inc(res, &(*f)->count, 1);
	}
	while (curr->next && curr->next->start)
	{
		curr = curr->next;
		if (((*res)->top - (*f)->count + 1 > 0 \
			&& curr->count + curr->x < (*res)->count + (*res)->x) \
			|| ((*res)->top - (*f)->count + 1 > 0 \
			&& curr->count - (*res)->count < (*res)->top - (*f)->count + 1))
		{
			curr->x += 1;
			curr->rooms->node->ant = (*f)->count;
			insert_act(act, curr->rooms->node->ant, curr->rooms->node->name, f);
			(*f)->count += 1;
		}
	}
}

static void	unset_rooms(t_list **rooms)
{
	while (*rooms)
	{
		if ((*rooms)->node->visited)
			(*rooms)->node->visited = 0;
		*rooms = (*rooms)->next;
	}
}

void		move_ants(t_node **res, t_act *act, t_node **farm, \
						long long int n)
{
	t_node			*curr;
	t_list			*rooms;

	(*farm)->count = n;
	(*res)->top = (*farm)->total;
	while ((*res)->res < (*farm)->total)
	{
		move_path(res, *res, &act, farm);
		curr = *res;
		while (curr)
		{
			if (curr->visited)
				curr->visited = 0;
			rooms = curr->rooms;
			unset_rooms(&rooms);
			curr = curr->next;
		}
		if ((*res)->top - (*farm)->count >= 0)
			i_like_to_move_it(res, *res, &act, farm);
		print_act(&act, act, farm);
	}
	if ((*farm)->end)
		ft_printf("OK\n");
}
