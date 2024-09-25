/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:58:38 by nyacoubi          #+#    #+#             */
/*   Updated: 2023/11/22 15:18:44 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	i;

	i = 1;
	while ((n / 10) != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	str_rev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

static void	int_convert(int n, char *nbr, int j)
{
	int	i;
	int	k;
	int	digits;

	i = 0;
	k = 1;
	digits = count_digits(n);
	if (n < 0)
	{
		j = 1;
		k = -1;
	}
	while (i < digits + j)
	{
		nbr[i] = (n % 10) * k + '0';
		n /= 10;
		i++;
	}
	if (j == 1)
	{
		nbr[digits] = '-';
		nbr[digits + j] = '\0';
	}
	else
		nbr[digits] = '\0';
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		j;

	j = 0;
	if (n < 0)
		j = 1;
	nbr = malloc((count_digits(n) + j + 1) * sizeof(char));
	if (!nbr)
		return (0);
	int_convert(n, nbr, j);
	str_rev(nbr);
	return (nbr);
}
