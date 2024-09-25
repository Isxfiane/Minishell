/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:38:44 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/04/12 11:14:57 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*r;

	if (s == NULL)
		return (NULL);
	r = malloc(ft_strlen(s) + 1);
	if (!r)
		return (0);
	ft_memcpy(r, s, ft_strlen(s) + 1);
	return (r);
}
