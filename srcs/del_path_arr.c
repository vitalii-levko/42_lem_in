/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:11:54 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 12:11:57 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		del_arr(char ***arr)
{
	char		**curr;
	char		*str;

	if (arr && *arr)
	{
		curr = *arr;
		while (*curr)
		{
			str = *curr;
			curr++;
			ft_strdel(&str);
		}
		free(*arr);
		*arr = NULL;
		arr = NULL;
	}
}

static void	del_path_unit(t_step **inner, t_tree **curr, int deep)
{
	if (deep == 1)
	{
		free((*inner)->next->unit);
		(*inner)->next->unit = NULL;
	}
	else if (deep == 0)
	{
		free((*inner)->next);
		(*inner)->next = NULL;
	}
	else if (deep == 2)
	{
		free((*inner)->unit);
		(*inner)->unit = NULL;
	}
	else if (deep == 3 && curr)
	{
		free((*curr)->steps);
		(*curr)->steps = NULL;
	}
}

static void	del_curr_unit(t_step **inner, t_step *outer)
{
	while (outer && outer->next && outer->next != *inner)
		outer = outer->next;
	if (outer && outer->next == *inner)
		del_path_unit(&outer, NULL, 0);
}

static void	try_del(t_tree **curr, t_step *inner)
{
	while (inner->next && inner->next->next)
		inner = inner->next;
	if (inner->next)
	{
		if (inner->next->unit && inner->next->unit->steps)
		{
			del_path(&inner->next->unit);
			del_path_unit(&inner, NULL, 1);
		}
		else if (inner->next->unit)
			del_path_unit(&inner, NULL, 1);
		if (inner->next)
			del_path_unit(&inner, NULL, 0);
	}
	if (inner->unit && inner->unit->steps)
	{
		del_path(&inner->unit);
		del_path_unit(&inner, NULL, 2);
	}
	else if (inner->unit)
		del_path_unit(&inner, NULL, 2);
	if (inner == (*curr)->steps)
		del_path_unit(NULL, curr, 3);
	else
		del_curr_unit(&inner, (*curr)->steps);
}

void		del_path(t_tree **path)
{
	t_tree		*curr;
	t_step		*steps;
	t_step		*next;

	steps = (*path)->steps;
	while (steps)
	{
		curr = steps->unit;
		while (curr->steps)
			try_del(&curr, curr->steps);
		free(steps->unit);
		steps->unit = NULL;
		next = steps->next;
		if (steps == (*path)->steps)
		{
			free(steps);
			(*path)->steps = NULL;
		}
		else
			free(steps);
		steps = next;
	}
}
