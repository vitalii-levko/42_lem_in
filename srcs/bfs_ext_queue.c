/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_ext_queue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:58:38 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 14:58:39 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_list	*create_queue(t_node **node)
{
	t_list		*queue;

	if (!(queue = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	queue->node = *node;
	queue->next = NULL;
	return (queue);
}

void			push_queue(t_list **queue, t_node **node, t_node **farm)
{
	t_list		*curr;

	(*node)->visited = 1;
	if (*queue)
	{
		curr = *queue;
		while (curr->next)
			curr = curr->next;
		curr->next = create_queue(node);
		if (!curr->next)
			malloc_err(5, "create_queue()", farm);
		return ;
	}
	*queue = create_queue(node);
	if (!(*queue))
		malloc_err(5, "create_queue()", farm);
}

int				is_paired(t_list **queue, t_list *rooms)
{
	while (rooms)
	{
		if ((*queue)->node == rooms->node)
			return (1);
		rooms = rooms->next;
	}
	return (0);
}
