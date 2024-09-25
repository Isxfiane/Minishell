/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:40:31 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/05/16 11:37:54 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strfind(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_str2cpy(char *src, char *src2, char *dest, ssize_t lenbuff)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (src != NULL && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (k != lenbuff)
	{
		dest[i] = src2[k];
		k++;
		i++;
		if (dest[i - 1] == '\n')
			break ;
	}
	dest[i] = '\0';
	return (dest);
}
