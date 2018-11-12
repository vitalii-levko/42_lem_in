/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:57:38 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 13:57:39 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_map(t_map **map, t_node **farm)
{
	t_map *curr;

	curr = *map;
	if (!(*farm)->end)
	{
		while (curr)
		{
			ft_printf("%s", curr->str);
			curr = curr->next;
		}
		ft_printf("\n");
	}
	else
	{
		while (curr)
		{
			ft_putstr_fd(curr->str, (*farm)->end);
			curr = curr->next;
		}
		ft_putstr_fd("\n", (*farm)->end);
	}
}

t_node	*create_top_node(long long int total, char e, char d, char s)
{
	t_node					*farm;

	if (!(farm = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	farm->total = total;
	farm->top = 0;
	farm->res = 0;
	farm->count = 0;
	farm->x = (e) ? 1 : 0;
	farm->y = (d) ? 1 : 0;
	farm->start = 0;
	farm->end = (s) ? 1 : 0;
	farm->weight = 0;
	farm->ant = 0;
	farm->visited = 0;
	farm->id = -1;
	farm->name = ft_strdup("total");
	farm->rooms = NULL;
	farm->next = NULL;
	return (farm);
}

int		check_opt(int ac, char *str)
{
	if (ac == 2)
	{
		if (!ft_strcmp("-e", str))
			return (1);
		else if (!ft_strcmp("-d", str))
			return (1);
		else if (!ft_strcmp("-s", str))
			return (1);
	}
	return (0);
}

void	save_opt(char *str, t_node **farm)
{
	if (!ft_strcmp("-e", str))
	{
		*farm = create_top_node(0, 1, 0, 0);
		if (!(*farm))
			exit(p_err(5, "Memory allocation failed", NULL, NULL));
	}
	else if (!ft_strcmp("-d", str))
	{
		*farm = create_top_node(0, 1, 1, 0);
		if (!(*farm))
			exit(p_err(5, "Memory allocation failed", NULL, NULL));
	}
	else if (!ft_strcmp("-s", str))
	{
		*farm = create_top_node(0, 1, 1, 1);
		if (!(*farm))
			exit(p_err(5, "Memory allocation failed", NULL, NULL));
	}
}
