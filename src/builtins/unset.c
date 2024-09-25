/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:33:00 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 17:44:30 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_all_inenv(char *envp, t_cmds *data)
{
	char	*tmp;
	int		i;

	if (!ft_strcmp(envp, "_"))
		return (0);
	i = 0;
	while (data->cmd_tab[i])
	{
		tmp = ft_strjoin(data->cmd_tab[i], "=");
		if (!tmp)
			return (-1);
		if (!ft_strncmp(envp, tmp, ft_strlen(tmp)))
			return (free(tmp), 1);
		free(tmp);
		i++;
	}
	return (0);
}

static char	**ft_newenv(int new, t_adr *perma, t_cmds *data, int len)
{
	char	**new_tab;
	int		i;
	int		j;

	if (!data->envp)
		return (NULL);
	new_tab = (char **)malloc(sizeof(char *) * (len + 1 + new));
	if (!new_tab)
		return (NULL);
	append_node(&perma, new_tab);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (!check_all_inenv(data->envp[i], data))
		{
			new_tab[j] = ft_strdup(data->envp[i]);
			if (!new_tab[j])
				return (NULL);
			append_node(&perma, new_tab[j]);
			j++;
		}
		i++;
	}
	return (new_tab[j] = NULL, append_node(&perma, new_tab[j]), new_tab);
}

static int	is_in_env(char **envp, char *str)
{
	char	*tmp;
	int		i;

	if (!ft_strcmp(str, "_"))
		return (0);
	i = 0;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (-1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(tmp)))
			return (free(tmp), 1);
		i++;
	}
	free(tmp);
	return (0);
}

void	builtins_unset(t_cmds *data, t_adr *perma)
{
	char	**new_env;
	int		i;
	int		count;

	if (!data->cmd_tab[1])
		return ;
	i = 1;
	count = 0;
	while (data->cmd_tab[i])
	{
		if (is_in_env(data->envp, data->cmd_tab[i]))
			count++;
		i++;
	}
	if (!count)
		return ;
	new_env = ft_newenv(count * -1, perma, data, ft_tablen(data->envp));
	if (!new_env)
		return ;
	data->envp = new_env;
}
