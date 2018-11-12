/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 11:53:51 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 11:55:05 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		exit_check(t_node **farm, int nb)
{
	if (farm && *farm)
		del_farm(farm);
	return (nb);
}

int		exit_parse(t_map **map, int nb, t_node **farm, char **str)
{
	if (farm && (*farm)->end)
	{
		ft_printf("KO\n");
		close((*farm)->end);
	}
	if (map && *map)
		del_map(map);
	if (farm && *farm)
		del_farm(farm);
	if (str && *str)
		ft_strdel(str);
	return (nb);
}

int		exit_search(t_node **farm, t_map **map, t_tree **path, t_node **res)
{
	if (farm && *farm && (*farm)->end)
	{
		ft_printf("KO\n");
		close((*farm)->end);
	}
	if (farm && *farm)
		del_farm(farm);
	if (map && *map)
		del_map(map);
	if (path && *path)
	{
		del_path(path);
		free(*path);
		*path = NULL;
	}
	if (res && *res)
		del_res(res);
	return (3);
}
