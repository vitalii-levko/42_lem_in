/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:32:10 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 13:32:12 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

char		**exit_room(char ***arr, int *e)
{
	if (e)
		*e = 1;
	if (arr)
		del_arr(arr);
	return (NULL);
}

static char	**r_err(char *str, char *orig, t_node **farm, int *e)
{
	p_err(1, str, orig, farm);
	return (exit_room(NULL, e));
}

static char	**is_room(char *str, int *e, int cmd, t_node **farm)
{
	char		**arr;

	arr = NULL;
	if (str)
	{
		if (*str == 'L')
			return (r_err("First latter 'L' usage is forbidden", str, farm, e));
		arr = ft_strsplit(str, ' ');
		if (arr_len(arr) != 3)
		{
			if (cmd)
				p_err(1, "Invalid room after previous command", str, farm);
			else if (!(*farm)->next || !(*farm)->next->next)
				return (r_err("Invalid room", str, farm, e));
			else
				*e = -1;
			return (exit_room(&arr, NULL));
		}
		if (is_num(arr[1], arr[1], farm, 0) || is_num(arr[2], arr[2], farm, 0))
			return (exit_room(&arr, e));
		if (is_int(arr[1], farm, 0, 0) || is_int(arr[2], farm, 0, 0))
			return (exit_room(&arr, e));
	}
	return (arr);
}

char		**check_if_room(char *str, int cmd, t_node **farm, int *e)
{
	char	**arr;

	arr = is_room(str, e, cmd, farm);
	if (!arr && cmd)
	{
		*e = 1;
		return (NULL);
	}
	if (*e)
		return (NULL);
	return (arr);
}
