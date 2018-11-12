/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:21:49 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:21:53 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		del_act(t_act **act)
{
	t_act	*curr;

	while (*act)
	{
		ft_strdel(&(*act)->room);
		curr = *act;
		*act = (*act)->next;
		free(curr);
		curr = NULL;
	}
}

static t_act	*new_act(long long int nb, char *room, t_node **farm)
{
	t_act		*act;

	if (!(act = (t_act *)malloc(sizeof(t_act))))
		malloc_err(5, "new_act()", farm);
	act->nb = nb;
	act->room = (room) ? ft_strdup(room) : NULL;
	act->next = NULL;
	return (act);
}

static void		append_act(t_act **act, long long int nb, char *room, \
							t_node **farm)
{
	t_act		*curr;
	t_act		*next;

	curr = *act;
	if (curr->nb < nb)
	{
		while (curr->next && curr->next->nb < nb)
			curr = curr->next;
		if (curr->next)
		{
			next = curr->next;
			curr->next = new_act(nb, room, farm);
			curr->next->next = next;
		}
		else
			curr->next = new_act(nb, room, farm);
	}
	else
	{
		*act = new_act(nb, room, farm);
		(*act)->next = curr;
	}
}

void			insert_act(t_act **act, long long int nb, char *room, \
							t_node **farm)
{
	if (*act)
		append_act(act, nb, room, farm);
	else
		*act = new_act(nb, room, farm);
}

void			print_act(t_act **act, t_act *curr, t_node **farm)
{
	int			sw;
	char		*str;

	sw = 0;
	while (curr)
	{
		if (sw != 0)
			((*farm)->end) ? ft_putstr_fd(" ", (*farm)->end) : ft_printf(" ");
		if ((*farm)->end)
		{
			ft_putstr_fd("L", (*farm)->end);
			str = ft_itol(curr->nb);
			ft_putstr_fd(str, (*farm)->end);
			ft_strdel(&str);
			ft_putstr_fd("-", (*farm)->end);
			ft_putstr_fd(curr->room, (*farm)->end);
		}
		else
			ft_printf("L%llu-%s", curr->nb, curr->room);
		sw = 1;
		curr = curr->next;
	}
	del_act(act);
	((*farm)->end) ? ft_putstr_fd("\n", (*farm)->end) : ft_printf("\n");
}
