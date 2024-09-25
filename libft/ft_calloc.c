/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:16:01 by nyacoubi          #+#    #+#             */
/*   Updated: 2023/11/29 14:37:51 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*t;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (0);
	t = malloc(nmemb * size);
	if (!t)
		return (0);
	ft_memset(t, 0, size * nmemb);
	return (t);
}
