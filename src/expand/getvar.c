/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:29:22 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/24 13:29:23 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_var(char *name, t_cmds *info)
{
	int		i;
	char	*var;

	i = 0;
	while (info->envp[i] != NULL)
	{
		var = get_name(info->envp[i]);
		if (ft_strcmp(var, name) == 0)
		{
			free(var);
			return (&info->envp[i][ft_strlen(name) + 1]);
		}
		i++;
		free(var);
	}
	return (NULL);
}
