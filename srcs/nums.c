/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:34:40 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:34:42 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	check_if_ret(int ret, t_node **farm)
{
	if (ret <= 0)
		return (p_err(1, "Unexpected end of input source", "", farm));
	return (0);
}

static int	is_less_or_zero(t_node **farm, char *orig)
{
	if ((*farm)->total <= 0)
	{
		return (p_err(1, "Number of ants is not a positive number", \
		orig, farm));
	}
	return (0);
}

static int	store_if_number(char *str, t_node **farm)
{
	if (is_num(str, str, farm, 1))
		return (1);
	if (is_int(str, farm, 1, 0))
		return (1);
	(*farm)->total = ft_atoi(str);
	if (is_less_or_zero(farm, str))
		return (1);
	return (0);
}

int			save_number_of_ants(int ret, char **str, t_map **map, t_node **farm)
{
	if (check_if_ret(ret, farm))
		return (1);
	if (is_command(*str, &ret))
		return (p_err(1, "Invalid command usage", *str, farm));
	while (is_comment(*str))
	{
		store_map(map, *str, farm);
		ft_strdel(str);
		ret = get_next_line(0, str);
		if (check_if_ret(ret, farm))
			return (1);
		if (is_command(*str, &ret))
			return (p_err(1, "Invalid command usage", *str, farm));
	}
	if (store_if_number(*str, farm))
		return (1);
	store_map(map, *str, farm);
	ft_strdel(str);
	return (0);
}
