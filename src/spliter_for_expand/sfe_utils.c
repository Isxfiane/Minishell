/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:01:54 by sben-rho          #+#    #+#             */
/*   Updated: 2024/04/12 14:30:52 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_hiden_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == -32 || s[i] == -9 || s[i] == -10)
			return (1);
		if (s[i] == -11 || s[i] == -12 || s[i] == -13)
			return (1);
		i++;
	}
	return (0);
}

int	count_hiden_space(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == -32 || s[i] == -9 || s[i] == -10)
			count++;
		if (s[i] == -11 || s[i] == -12 || s[i] == -13)
			count++;
		i++;
	}
	return (count);
}
