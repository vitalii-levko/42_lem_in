/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:14:39 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 13:14:41 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			is_comment(char *str)
{
	if (str)
	{
		if (str[0] && str[0] == '#')
			return (1);
	}
	return (0);
}

static int	is_same(char **arr, char **str, t_node **farm)
{
	if (!ft_strcmp(arr[0], arr[1]))
		return (p_err(1, "Invalid link to the same room", *str, farm));
	return (0);
}

static int	is_connection(t_node **curr, int *a, int *b, char **arr)
{
	if (!(*a) && !ft_strcmp((*curr)->name, arr[0]))
		*a = 1;
	else if (!(*b) && !ft_strcmp((*curr)->name, arr[1]))
		*b = 1;
	else if (*a && *b)
		return (1);
	return (0);
}

int			if_connects(t_node **farm, t_node *curr, char **arr, char **str)
{
	int			connection_a;
	int			connection_b;

	connection_a = 0;
	connection_b = 0;
	if (is_same(arr, str, farm))
		return (1);
	while (curr)
	{
		if (curr->id != -1)
		{
			if (is_connection(&curr, &connection_a, &connection_b, arr))
				return (0);
		}
		curr = curr->next;
	}
	if (!connection_a && !connection_b)
		return (p_err(1, "Linking rooms do not exist", *str, farm));
	else if (!connection_a)
		return (p_err(1, "Linking room does not exists", arr[0], farm));
	else if (!connection_b)
		return (p_err(1, "Linking room does not exists", arr[1], farm));
	return (0);
}

int			check_farm(t_node **farm, t_node *curr, int start, int end)
{
	while (curr)
	{
		if (curr->id != -1)
		{
			if (!start && curr->start)
				start = 1;
			else if (curr->start)
				return (p_err(1, "Second 'start' room was found", \
					curr->name, farm));
			else if (!end && curr->end)
				end = 1;
			else if (curr->end)
				return (p_err(1, "Second 'end' room was found", \
					curr->name, farm));
		}
		curr = curr->next;
	}
	if (!start && !end)
		return (p_err(1, "Neither 'start' nor 'end' room did not found", \
			NULL, farm));
	else if (!start)
		return (p_err(1, "'start' room did not found", NULL, farm));
	if (!end)
		return (p_err(1, "'end' room did not found", NULL, farm));
	return (0);
}
