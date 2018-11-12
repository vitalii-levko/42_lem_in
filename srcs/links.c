/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:53:02 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:53:04 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	if_exists_rev(t_node **farm, char **arr, char **str)
{
	t_node		*curr;
	t_list		*rooms;

	curr = *farm;
	while (curr)
	{
		if (!ft_strcmp(curr->name, arr[1]))
		{
			rooms = curr->rooms;
			while (rooms)
			{
				if (!ft_strcmp(rooms->node->name, arr[0]))
				{
					return (p_err(1, "Link in reversed format already exists", \
					*str, farm));
				}
				rooms = rooms->next;
			}
		}
		curr = curr->next;
	}
	return (0);
}

static int	if_exists(t_node **farm, char **arr, char **str)
{
	t_node		*curr;
	t_list		*rooms;

	curr = *farm;
	while (curr)
	{
		if (!ft_strcmp(curr->name, arr[0]))
		{
			rooms = curr->rooms;
			while (rooms)
			{
				if (!ft_strcmp(rooms->node->name, arr[1]))
					return (p_err(1, "Link already exists", *str, farm));
				rooms = rooms->next;
			}
		}
		curr = curr->next;
	}
	return (0);
}

static char	**is_link(char *str, char **arr)
{
	if (str)
	{
		arr = ft_strsplit(str, '-');
		if (arr_len(arr) != 2)
		{
			del_arr(&arr);
			return (NULL);
		}
		return (arr);
	}
	return (NULL);
}

static char	**check_if_link(char *str, char **arr, int *e, t_node **farm)
{
	arr = is_link(str, NULL);
	if (!arr)
	{
		p_err(1, "Invalid link", str, farm);
		*e = 1;
		return (NULL);
	}
	return (arr);
}

int			parse_link(t_node **farm, char **str)
{
	char		**arr;
	int			e;

	e = 0;
	arr = check_if_link(*str, NULL, &e, farm);
	if (e)
	{
		del_arr(&arr);
		return (1);
	}
	if (if_connects(farm, *farm, arr, str))
	{
		del_arr(&arr);
		return (1);
	}
	if (if_exists(farm, arr, str) || if_exists_rev(farm, arr, str))
	{
		del_arr(&arr);
		return (1);
	}
	store_link(farm, arr);
	del_arr(&arr);
	return (0);
}
