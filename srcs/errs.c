/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:32:08 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:32:10 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	p_err_fd(char *str, char *orig, t_node **farm)
{
	ft_putstr_fd("ERROR: ", (*farm)->end);
	ft_putendl_fd(str, (*farm)->end);
	if (orig)
	{
		if ((*farm)->ant)
		{
			ft_printf("Program terminated unexpectedly. See log file.\n");
			ft_putstr_fd(">>> function", (*farm)->end);
		}
		else
		{
			ft_putstr_fd(">>> line ", (*farm)->end);
			ft_putstr_fd(ft_itol((*farm)->weight + 1), (*farm)->end);
		}
		ft_putstr_fd(": '", (*farm)->end);
		ft_putstr_fd(orig, (*farm)->end);
		ft_putendl_fd("'", (*farm)->end);
	}
}

int			p_err(int ret, char *str, char *orig, t_node **farm)
{
	if (farm && *farm && !(*farm)->end)
	{
		if ((*farm)->x)
		{
			ft_printf("ERROR: %s\n", str);
			if (orig && (*farm)->y)
			{
				if ((*farm)->ant)
					ft_printf(">>> function: '%s'\n", orig);
				else
					ft_printf(">>> line %lld: '%s'\n", (*farm)->weight + 1, \
						orig);
			}
		}
		else
			ft_printf("ERROR\n");
	}
	else if (farm && *farm)
		p_err_fd(str, orig, farm);
	else
		ft_printf("ERROR: %s\n", str);
	return (ret);
}

void		malloc_err(int ret, char *orig, t_node **farm)
{
	(*farm)->ant = 1;
	exit(p_err(ret, "Memory allocation failed", orig, farm));
}
