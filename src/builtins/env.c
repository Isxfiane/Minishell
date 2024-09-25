/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:01:55 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 17:47:56 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_tabdup(char **tab, int new, t_adr *perma)
{
	char	**new_tab;
	int		i;

	if (!tab)
		return (NULL);
	new_tab = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1 + new));
	if (!new_tab)
		return (NULL);
	append_node(&perma, new_tab);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		append_node(&perma, new_tab[i]);
		if (!new_tab[i])
			return (NULL);
		i++;
	}
	new_tab[i] = (NULL);
	append_node(&perma, new_tab[i]);
	return (new_tab);
}

static char	*set_pwd(t_cmds *data, t_adr *adr, t_adr *perma, char *pwd)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = NULL;
	if (pwd)
	{
		append_node(&adr, pwd);
		while (data->envp[i] && !ft_strnstr(data->envp[i], "PWD", 3))
			i++;
		if (data->envp[i])
		{
			old_pwd = data->envp[i];
			data->envp[i] = ft_strjoin("PWD=", pwd);
			append_node(&perma, data->envp[i]);
		}
	}
	return (old_pwd);
}

static int	no_env(t_cmds *data, t_adr *perma, char *pwd)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * 4);
	if (!new_env)
		return (-1);
	append_node(&perma, new_env);
	new_env[0] = ft_strjoin("PWD=", pwd);
	if (!new_env[0])
		return (-1);
	append_node(&perma, new_env[0]);
	new_env[1] = ft_strdup("SHLVL=1");
	if (!new_env[1])
		return (-1);
	append_node(&perma, new_env[1]);
	new_env[2] = ft_strdup("_=/usr/bin/env");
	if (!new_env[2])
		return (-1);
	append_node(&perma, new_env[2]);
	new_env[3] = NULL;
	data->envp = new_env;
	return (0);
}

int	init_env(t_cmds *data, t_adr *adr, t_adr *perma)
{
	int		i;
	char	*pwd;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	old_pwd = set_pwd(data, adr, perma, pwd);
	if (!data->envp[0])
		return (no_env(data, perma, pwd));
	i = 0;
	while (data->envp[i] && !ft_strnstr(data->envp[i], "OLDPWD", 6))
		i++;
	if (!data->envp[i] || !old_pwd)
		return (0);
	data->envp[i] = ft_strjoin("OLDPWD=", old_pwd + 4);
	append_node(&perma, data->envp[i]);
	return (0);
}

void	builtins_env(t_cmds *data, t_adr *adr, t_adr *perma)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
	end_builtin(data, adr, perma);
	exit(0);
}
