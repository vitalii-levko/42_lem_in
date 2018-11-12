/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:05:10 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 15:05:12 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_tree			*create_unit(t_node **node, t_tree **parent)
{
	t_tree		*unit;

	if (!(unit = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	unit->node = *node;
	unit->parent = (parent) ? *parent : NULL;
	unit->steps = NULL;
	return (unit);
}

static t_step	*create_step(t_node **node, t_tree **parent, t_node **farm)
{
	t_step		*step;

	if (!(step = (t_step *)malloc(sizeof(t_step))))
		return (NULL);
	step->next = NULL;
	step->unit = create_unit(node, parent);
	if (!step->unit)
		malloc_err(5, "create_unit()", farm);
	return (step);
}

void			append_step(t_tree **unit, t_node **node, t_node **farm)
{
	t_step		*curr;

	if (*unit)
	{
		curr = (*unit)->steps;
		if ((*unit)->steps)
		{
			while (curr->next)
				curr = curr->next;
			curr->next = create_step(node, unit, farm);
			if (!curr->next)
				malloc_err(5, "create_step()", farm);
			return ;
		}
		(*unit)->steps = create_step(node, unit, farm);
		if (!(*unit)->steps)
			malloc_err(5, "create_step()", farm);
	}
}
