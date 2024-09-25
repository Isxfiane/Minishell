/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:19 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/03/28 13:23:14 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>

static int	fill_nbr(const char *nptr, size_t i, int s, long long nbr)
{
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nbr * s > (LLONG_MAX - (nptr[i] - 48)) / 10)
			return (-1);
		if (nbr * s < (LLONG_MIN + (nptr[i] - 48)) / 10)
			return (0);
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return ((int)nbr * s);
}

int	ft_atoi(const char *nptr)
{
	long long	nbr;
	size_t		i;
	int			s;

	i = 0;
	s = 1;
	nbr = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (!((nptr[i] >= '0' && nptr[0] <= '9')
			|| (nptr[i] == '-' || nptr[i] == '+')))
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	return (fill_nbr(nptr, i, s, nbr));
}
