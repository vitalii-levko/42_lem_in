/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:12:12 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 15:12:12 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*create_node(char *name, long long int x, long long int y, int cmd)
{
	t_node					*farm;
	static long long int	id = 0;

	if (!(farm = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	farm->total = 0;
	farm->top = 0;
	farm->res = 0;
	farm->count = 0;
	farm->x = (int)x;
	farm->y = (int)y;
	farm->start = (cmd == 's') ? 1 : 0;
	farm->end = (cmd == 'e') ? 1 : 0;
	farm->weight = 0;
	farm->ant = 0;
	farm->visited = 0;
	farm->id = id++;
	farm->name = ft_strcpy(ft_strnew(ft_strlen(name)), name);
	farm->rooms = NULL;
	farm->next = NULL;
	return (farm);
}

void	reset_it(t_node **farm)
{
	t_node		*curr;

	curr = *farm;
	while (curr)
	{
		curr->ant = 0;
		curr = curr->next;
	}
}
