/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_res.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:09:09 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 15:09:10 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void				copy_node(t_node **node, t_node **copy)
{
	(*copy)->total = (*node)->total;
	(*copy)->top = (*node)->top;
	(*copy)->res = (*node)->res;
	(*copy)->count = (*node)->count;
	(*copy)->x = (*node)->x;
	(*copy)->y = (*node)->y;
	(*copy)->start = (*node)->start;
	(*copy)->end = (*node)->end;
	(*copy)->weight = (*node)->weight;
	(*copy)->ant = (*node)->ant;
	(*copy)->visited = (*node)->visited;
	(*copy)->id = (*node)->id;
	(*copy)->name = ft_strdup((*node)->name);
	(*copy)->rooms = NULL;
	(*copy)->next = NULL;
}

static t_list			*popup_wrap(t_node **node, t_list **wrap, t_node **farm)
{
	t_list		*curr;

	if (!(curr = (t_list *)malloc(sizeof(t_list))))
		malloc_err(5, "popup_wrap()", farm);
	curr->next = *wrap;
	if (!(curr->node = (t_node *)malloc(sizeof(t_node))))
		malloc_err(5, "popup_wrap()", farm);
	copy_node(node, &curr->node);
	return (curr);
}

static long long int	count_nodes(t_list *rooms)
{
	long long int	count;

	count = 0;
	while (rooms && !rooms->node->end)
	{
		count++;
		rooms = rooms->next;
	}
	return (count);
}

static t_node			*store_res(t_tree **unit, t_node **node, t_node **farm)
{
	t_node		*res;
	t_list		*wrap;
	t_tree		*curr;

	if (!(res = (t_node *)malloc(sizeof(t_node))))
		malloc_err(5, "store_res()", farm);
	if (!(wrap = (t_list *)malloc(sizeof(t_list))))
		malloc_err(5, "store_res()", farm);
	wrap->next = NULL;
	if (!(wrap->node = (t_node *)malloc(sizeof(t_node))))
		malloc_err(5, "store_res()", farm);
	copy_node(node, &wrap->node);
	curr = *unit;
	while (curr->parent)
	{
		curr->node->res = 1;
		wrap = popup_wrap(&curr->node, &wrap, farm);
		curr = curr->parent;
	}
	copy_node(&curr->node, &res);
	res->rooms = wrap;
	if (!res->count)
		res->count = count_nodes(res->rooms);
	return (res);
}

void					end_point(t_tree **unit, t_node **node, t_node **res, \
						t_node **farm)
{
	t_node		*curr;

	if (*res)
	{
		curr = *res;
		while (curr->next)
			curr = curr->next;
		curr->next = store_res(unit, node, farm);
	}
	else
		*res = store_res(unit, node, farm);
}
