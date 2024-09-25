/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:48:07 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/02/20 15:41:37 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_fdigits(long long nbr)
{
	int	i;

	i = 1 + (nbr < 0);
	while ((nbr / 10) != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	count_hexdigits(size_t nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

int	print_uint(size_t nbr)
{
	int	len;

	len = count_fdigits(nbr);
	if (nbr > 9)
	{
		print_uint(nbr / 10);
		print_uint(nbr % 10);
	}
	if (nbr <= 9)
		print_char(nbr + '0');
	return (len);
}

int	print_nbr(int nbr)
{
	int	len;

	len = count_fdigits(nbr);
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (len);
	}
	else if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		print_nbr(nbr / 10);
		print_nbr(nbr % 10);
	}
	if (nbr <= 9 && nbr >= 0)
		print_char(nbr + '0');
	return (len);
}
