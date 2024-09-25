/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:33 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/02/20 15:37:56 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	argset(char argtype, va_list args)
{
	int	printlen;

	printlen = 0;
	if (argtype == 'c')
		printlen += print_char(va_arg(args, int));
	else if (argtype == 's')
		printlen += print_str((va_arg(args, char *)));
	else if (argtype == 'p')
		printlen += print_ptr((va_arg(args, size_t)));
	else if (argtype == 'd' || argtype == 'i')
		printlen += print_nbr(va_arg(args, int));
	else if (argtype == 'u')
		printlen += print_uint(va_arg(args, unsigned int));
	else if (argtype == 'x')
		printlen += print_hexlow(va_arg(args, unsigned int));
	else if (argtype == 'X')
		printlen += print_hexup(va_arg(args, unsigned int));
	else if (argtype == '%')
		printlen += write(1, "%", 1);
	else
		return (-1);
	return (printlen);
}

int	argcheck(const char *s, va_list args)
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
			printlen += write (1, &s[i], 1);
			i++;
		}
		else
		{
			check = argset(s[i + 1], args);
			if (check == -1)
				return (-1);
			printlen += check;
			i += 2;
		}
	}
	return (printlen);
}

int	ft_printf(const char *s, ...)
{
	int		printlen;
	va_list	args;

	va_start(args, s);
	if (write(1, 0, 0) == -1)
		return (-1);
	printlen = argcheck(s, args);
	va_end(args);
	return (printlen);
}
