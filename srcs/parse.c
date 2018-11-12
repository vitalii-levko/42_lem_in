/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:54:10 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:54:13 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			is_command(char *str, int *cmd)
{
	if (str)
	{
		if (!ft_strcmp(str, "##start"))
		{
			*cmd = 's';
			return (1);
		}
		else if (!ft_strcmp(str, "##end"))
		{
			*cmd = 'e';
			return (1);
		}
	}
	return (0);
}

static int	save_if_link(t_node **farm, char **str, int cmd)
{
	if (is_command(*str, &cmd))
	{
		return (p_err(1, "Room after previous command did not found", *str, \
		farm));
	}
	if (is_comment(*str))
		return (0);
	if (parse_link(farm, str))
		return (1);
	return (0);
}

static int	save_if_link_more(t_node **farm, char **str, int cmd)
{
	if (is_command(*str, &cmd))
		return (p_err(1, "Same command used twice", *str, farm));
	if (is_comment(*str))
		return (0);
	if (parse_link(farm, str))
		return (1);
	return (0);
}

static int	save_the_links(t_node **farm, char **str, int cmd, t_map **map)
{
	if (*str)
	{
		if (check_farm(farm, *farm, 0, 0) || save_if_link(farm, str, cmd))
			return (1);
		store_map(map, *str, farm);
		ft_strdel(str);
	}
	else
		return (p_err(1, "Unexpected end of input source", "", farm));
	while (get_next_line(0, str) > 0)
	{
		if (save_if_link_more(farm, str, cmd))
			return (1);
		store_map(map, *str, farm);
		ft_strdel(str);
	}
	ft_strdel(str);
	return (0);
}

int			parse_map(t_node **farm, char *str, t_map **map)
{
	if (save_number_of_ants(get_next_line(0, &str), &str, map, farm))
		return (exit_parse(NULL, 1, NULL, &str));
	if (save_the_rooms(farm, &str, 0, map))
		return (exit_parse(NULL, 1, NULL, &str));
	if (save_the_links(farm, &str, 0, map))
		return (exit_parse(NULL, 1, NULL, &str));
	return (0);
}
