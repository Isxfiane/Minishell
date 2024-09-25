/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:09:33 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 13:40:42 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtins_control(t_cmds *data, t_adr *perma, t_adr *adr)
{
	if (data->cmd_tab[0])
	{
		data->status_set = 1;
		if (!data->next && !ft_strcmp(data->cmd_tab[0], "cd"))
		{
			g_status = builtins_cd(data, adr);
			return (1);
		}
		if (!data->next && !ft_strcmp(data->cmd_tab[0], "exit"))
		{
			builtins_exit(data, adr, perma);
			return (1);
		}
		if (!data->next && !ft_strcmp(data->cmd_tab[0], "export")
			&& data->cmd_tab)
		{
			g_status = 0;
			return (builtins_export(data, perma), 1);
		}
		if (!data->next && !ft_strcmp(data->cmd_tab[0], "unset"))
			return (builtins_unset(data, perma), 1);
	}
	return (data->status_set = 0, 0);
}

int	check_if_builtins(t_cmds *data)
{
	char	*cmd;

	cmd = data->cmd_tab[0];
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static int	flag_nonewline(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtins_echo(t_cmds *data, t_adr *adr, t_adr *perma)
{
	int	i;

	if (data->prev_pipe)
	{
		close (data->prev_pipe[0]);
		close (data->prev_pipe[1]);
	}
	if (ft_tablen(data->cmd_tab) == 1)
		return (ft_printf("\n"), end_builtin(data, adr, perma), exit(0));
	i = 1;
	while (data->cmd_tab[i] && flag_nonewline(data->cmd_tab[i]))
		i++;
	while (data->cmd_tab[i])
	{
		ft_putstr_fd(data->cmd_tab[i], 1);
		if (data->cmd_tab[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!flag_nonewline(data->cmd_tab[1]))
		ft_printf("\n");
	return (end_builtin(data, adr, perma), exit(0));
}

int	exec_builtins(t_cmds *data, t_adr *address, t_adr *perma)
{
	if (!ft_strcmp(data->cmd_tab[0], "echo"))
		return (builtins_echo(data, address, perma), 0);
	if (!ft_strcmp(data->cmd_tab[0], "pwd"))
		return (builtins_pwd(data, address, perma), 0);
	if (!ft_strcmp(data->cmd_tab[0], "env"))
		return (builtins_env(data, address, perma), 0);
	if (!ft_strcmp(data->cmd_tab[0], "export") && !data->cmd_tab[1])
		return (builtins_export(data, perma), -1);
	return (-1);
}
