/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:55:15 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/04 11:18:09 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	if (str == NULL)
		return (write (1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	print_hexlow(size_t	nbr)
{
	char	*str;
	int		len;

	len = count_hexdigits(nbr);
	str = "0123456789abcdef";
	if (nbr < 16)
		print_char(str[nbr]);
	else
	{
		print_hexlow(nbr / 16);
		print_hexlow(nbr % 16);
	}
	return (len);
}

int	print_hexup(size_t nbr)
{
	char	*str;
	int		len;

	len = count_hexdigits(nbr);
	str = "0123456789ABCDEF";
	if (nbr < 16)
		print_char(str[nbr]);
	else
	{
		print_hexup(nbr / 16);
		print_hexup(nbr % 16);
	}
	return (len);
}

int	print_ptr(size_t ptr)
{
	if (!ptr)
		return (write (1, "(nil)", 5));
	write(1, "0x", 2);
	return (print_hexlow(ptr) + 2);
}
