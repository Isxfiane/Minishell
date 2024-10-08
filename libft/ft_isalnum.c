/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:41:56 by nyacoubi          #+#    #+#             */
/*   Updated: 2023/11/22 15:18:34 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (!((c >= 65 && c <= 90) || (c >= 97
				&& c <= 122) || (c >= 48 && c <= 57)))
		return (0);
	return (1);
}
