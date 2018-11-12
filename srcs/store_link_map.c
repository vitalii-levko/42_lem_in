/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stores.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:11:05 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 13:11:07 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_map	*new_map(char *str)
{
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->str = ft_strjoin(str, "\n");
	map->next = NULL;
	return (map);
}

void			store_map(t_map **map, char *str, t_node **farm)
{
	t_map		*curr;

	(*farm)->weight += 1;
	if (*map)
	{
		curr = *map;
		while (curr->next)
			curr = curr->next;
		curr->next = new_map(str);
		if (!curr->next)
			malloc_err(5, "new_map()", farm);
	}
	else
		*map = new_map(str);
	if (!(*map))
		malloc_err(5, "new_map()", farm);
}

static int		create_link(t_node *dst, t_node *curr)
{
	t_list		*link;
	t_list		*rooms;

	if (!(link = (t_list *)malloc(sizeof(t_list))))
		return (1);
	link->next = NULL;
	link->node = curr;
	if (dst->rooms)
	{
		rooms = dst->rooms;
		while (rooms->next)
			rooms = rooms->next;
		rooms->next = link;
	}
	else
		dst->rooms = link;
	return (0);
}

static void		append_link(t_node **farm, t_node *dst, char *link)
{
	t_node		*curr;

	curr = *farm;
	while (curr)
	{
		if (curr->id != -1)
		{
			if (!ft_strcmp(curr->name, link))
			{
				if (create_link(dst, curr))
					malloc_err(5, "create_link()", farm);
				return ;
			}
		}
		curr = curr->next;
	}
}

void			store_link(t_node **farm, char **arr)
{
	t_node		*curr;

	curr = *farm;
	while (curr)
	{
		if (curr->id != -1)
		{
			if (!ft_strcmp(curr->name, arr[0]))
			{
				append_link(farm, curr, arr[1]);
				return ;
			}
		}
		curr = curr->next;
	}
}
