/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:44:50 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:44:52 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	store_room(t_node **farm, char **arr, int cmd)
{
	t_node		*curr;

	if (*farm)
	{
		curr = *farm;
		while (curr->next)
			curr = curr->next;
		curr->next = create_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]), cmd);
		if (!curr->next)
			malloc_err(5, "create_node()", farm);
	}
	else
		*farm = create_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]), cmd);
	if (!(*farm))
		malloc_err(5, "create_node()", farm);
}

static int	is_duplicate(t_node **farm, t_node *curr, char **arr, char **str)
{
	int			x;
	int			y;
	char		*co;

	x = (int)ft_atoi(arr[1]);
	y = (int)ft_atoi(arr[2]);
	while (curr)
	{
		if (curr->id != -1 && !ft_strcmp(curr->name, arr[0]))
		{
			p_err(1, "Room with the same name already exists", arr[0], farm);
			exit_room(&arr, NULL);
			return (1);
		}
		else if (curr->id != -1 && curr->x == x && curr->y == y)
		{
			co = ft_strchr(*str, ' ');
			exit_room(&arr, NULL);
			p_err(1, "Room with the same coordinates already exists", co, farm);
			co = NULL;
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	parse_room(t_node **farm, char **str, int *cmd, int *er)
{
	char		**arr;
	int			e;

	e = 0;
	arr = check_if_room(*str, *cmd, farm, &e);
	if (e == 1)
	{
		*er = -1;
		return (-1);
	}
	if (e == -1)
		return (1);
	if (!arr)
		return (1);
	if (is_duplicate(farm, *farm, arr, str))
	{
		*er = -1;
		return (-1);
	}
	store_room(farm, arr, *cmd);
	exit_room(&arr, NULL);
	*cmd = 0;
	return (0);
}

static int	is_dbl(char *str, t_node **farm)
{
	t_node	*curr;

	curr = *farm;
	while (curr)
	{
		if (curr->id != -1)
		{
			if ((!ft_strcmp("##start", str) && curr->start) \
			|| (!ft_strcmp("##end", str) && curr->end))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int			save_the_rooms(t_node **farm, char **str, int cmd, t_map **map)
{
	int			tmp;
	int			er;

	er = 0;
	while (get_next_line(0, str) > 0)
	{
		if (cmd && is_command(*str, &tmp))
			return (p_err(1, "Invalid command usage", *str, farm));
		if (is_command(*str, &cmd) || is_comment(*str))
		{
			if (is_dbl(*str, farm))
				return (p_err(1, "Same command used twice", *str, farm));
			store_map(map, *str, farm);
			ft_strdel(str);
			continue;
		}
		if (parse_room(farm, str, &cmd, &er) == 1)
			break ;
		else if (er == -1)
			return (1);
		store_map(map, *str, farm);
		ft_strdel(str);
	}
	return (0);
}
