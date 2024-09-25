/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:08:56 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 14:12:44 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	err_argset(char argtype, va_list args)
{
	int	printlen;

	printlen = 0;
	if (argtype == 'c')
		printlen += err_print_char(va_arg(args, int));
	else if (argtype == 's')
		printlen += err_print_str((va_arg(args, char *)));
	else if (argtype == 'p')
		printlen += err_print_ptr((va_arg(args, size_t)));
	else if (argtype == 'd' || argtype == 'i')
		printlen += err_print_nbr(va_arg(args, int));
	else if (argtype == 'u')
		printlen += err_print_uint(va_arg(args, unsigned int));
	else if (argtype == 'x')
		printlen += err_print_hexlow(va_arg(args, unsigned int));
	else if (argtype == 'X')
		printlen += err_print_hexup(va_arg(args, unsigned int));
	else if (argtype == '%')
		printlen += write(2, "%", 1);
	else
		return (-1);
	return (printlen);
}

int	err_argcheck(const char *s, va_list args)
{
	size_t	i;
	int		printlen;
	int		check;

	i = 0;
	printlen = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			printlen += write (2, &s[i], 1);
			i++;
		}
		else
		{
			check = err_argset(s[i + 1], args);
			if (check == -1)
				return (-1);
			printlen += check;
			i += 2;
		}
	}
	return (printlen);
}

int	ft_printf_err(const char *s, ...)
{
	int		printlen;
	va_list	args;

	va_start(args, s);
	if (write(2, 0, 0) == -1)
		return (-1);
	printlen = err_argcheck(s, args);
	va_end(args);
	return (printlen);
}

int	err_print_uint(size_t nbr)
{
	int	len;

	len = count_fdigits(nbr);
	if (nbr > 9)
	{
		err_print_uint(nbr / 10);
		err_print_uint(nbr % 10);
	}
	if (nbr <= 9)
		err_print_char(nbr + '0');
	return (len);
}

int	err_print_nbr(int nbr)
{
	int	len;

	len = count_fdigits(nbr);
	if (nbr == -2147483648)
	{
		write(2, "-2147483648", 11);
		return (len);
	}
	else if (nbr < 0)
	{
		write(2, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		err_print_nbr(nbr / 10);
		err_print_nbr(nbr % 10);
	}
	if (nbr <= 9 && nbr >= 0)
		err_print_char(nbr + '0');
	return (len);
}
