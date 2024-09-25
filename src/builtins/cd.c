/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:29:44 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 14:51:14 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return (1);
		i++;
	}
	return (0);
}

int	builtins_cd(t_cmds *data, t_adr *adr)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	append_node(&adr, old_pwd);
	if (tab_len(data->cmd_tab) > 2)
		return (ft_putstr_fd("cd", 2), ft_putendl_fd(ARG_ERR, 2), 1);
	if (tab_len(data->cmd_tab) == 1 && !check_home(data->envp))
		return (printf("cd: HOME not set\n"), 1);
	if (tab_len(data->cmd_tab) == 1)
		chdir(getenv("HOME"));
	else
	{
		if (chdir(data->cmd_tab[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(data->cmd_tab[1], 2);
			ft_putendl_fd(FD_ERR, 2);
			return (1);
		}
	}
	return (0);
}
