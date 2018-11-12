/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:34:09 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 13:34:10 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	is_max(char *str, long long int *val)
{
	char	*cmp;
	char	*cpy;

	cmp = ft_strdup("9223372036854775807");
	cpy = cmp;
	if (*str == '-')
		str++;
	while (*str)
	{
		*val = ft_strcmp(str, cmp);
		if (*val > 0)
			break ;
		str++;
		cmp++;
	}
	ft_strdel(&cpy);
}

int			arr_len(char **arr)
{
	int			len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

int			is_num(char *str, char *orig, t_node **farm, int cs)
{
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (!*str)
		{
			if (cs)
				return (p_err(1, "Number of ants did not found", orig, farm));
			else
				return (p_err(1, "Room coordinates did not found", orig, farm));
		}
		while (*str)
		{
			if (!ft_isdigit(*str))
			{
				(cs) ? p_err(1, "Number of ants is not a number", orig, farm) \
				: p_err(1, "Room coordinate is not a number", orig, farm);
				return (1);
			}
			str++;
		}
	}
	return (0);
}

int			is_int(char *str, t_node **farm, int cs, long long int val)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 19)
		return (0);
	if (len == 19)
		is_max(str, &val);
	if (len > 19 || val > 0)
	{
		if (cs)
			return (p_err(1, "Number of ants does not fit in 'long long int' \
				type", str, farm));
		else
			return (p_err(1, "Room coordinate does not fit in 'long long int' \
				type", str, farm));
	}
	return (0);
}
