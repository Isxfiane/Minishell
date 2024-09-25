/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:10:57 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/04 11:12:33 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	err_print_char(int c)
{
	return (write(2, &c, 1));
}

int	err_print_str(char *str)
{
	if (str == NULL)
		return (write (2, "(null)", 6));
	return (write(2, str, ft_strlen(str)));
}

int	err_print_hexlow(size_t	nbr)
{
	char	*str;
	int		len;

	len = count_hexdigits(nbr);
	str = "0123456789abcdef";
	if (nbr < 16)
		err_print_char(str[nbr]);
	else
	{
		err_print_hexlow(nbr / 16);
		err_print_hexlow(nbr % 16);
	}
	return (len);
}

int	err_print_hexup(size_t nbr)
{
	char	*str;
	int		len;

	len = count_hexdigits(nbr);
	str = "0123456789ABCDEF";
	if (nbr < 16)
		err_print_char(str[nbr]);
	else
	{
		err_print_hexup(nbr / 16);
		err_print_hexup(nbr % 16);
	}
	return (len);
}

int	err_print_ptr(size_t ptr)
{
	if (!ptr)
		return (write (2, "(nil)", 5));
	write(2, "0x", 2);
	return (err_print_hexlow(ptr) + 2);
}
