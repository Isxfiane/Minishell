/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:36:06 by nyacoubi          #+#    #+#             */
/*   Updated: 2023/11/22 15:30:46 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = start;
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (!s || start > ft_strlen(s))
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	while (j < ft_strlen(s) && i < len)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
