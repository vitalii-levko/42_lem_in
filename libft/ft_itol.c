/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 11:45:02 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/15 11:45:55 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_itolifneg(long long int *n, long long int *count, size_t *i, \
						char *str)
{
	if (*n < 0)
	{
		if (*n == -9223372036854775807)
		{
			str[0] = '-';
			str[1] = '9';
			*n = 223372036854775807;
			*count = *count / 10;
			*i = 2;
		}
		else
		{
			str[0] = '-';
			*i = 1;
			*n = -*n;
		}
	}
	else
		*i = 0;
}

static void	ft_itolcount(long long int *n, long long int *count, size_t *i)
{
	if (*n < 0)
		*n = -*n;
	while (*n / 10)
	{
		*count = *count * 10;
		*i = *i + 1;
		*n = *n / 10;
	}
}

char		*ft_itol(long long int n)
{
	long long int	count;
	long long int	tmp;
	char			*str;
	size_t			i;

	count = 1;
	i = 1;
	tmp = n;
	if (n < 0)
		i++;
	ft_itolcount(&n, &count, &i);
	if (!(str = ft_strnew(i)))
		return (NULL);
	ft_itolifneg(&tmp, &count, &i, str);
	while (count / 10)
	{
		str[i] = (char)((tmp / count) + '0');
		tmp = tmp % count;
		count = count / 10;
		i++;
	}
	str[i] = (char)(tmp + '0');
	return (str);
}
