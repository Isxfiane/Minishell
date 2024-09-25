/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:19:16 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 15:10:57 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	prepare_exec(t_cmds *data, t_adr *adr, t_adr *perma)
{
	if (!ft_strcmp(data->cmd_tab[0], "cd")
		|| !ft_strcmp(data->cmd_tab[0], "exit"))
		return (-1);
	else if (check_if_builtins(data))
		return (exec_builtins(data, adr, perma));
	if (ft_strchr(data->cmd_tab[0], '/'))
	{
		if (execve(data->cmd_tab[0], data->cmd_tab, data->envp) == -1)
		{
			g_status = 126;
			if (is_directory(data->cmd_tab[0]))
				return (ft_printf_err("%s: Is a directory\n"
						, data->cmd_tab[0]), -1);
			else if (access(data->cmd_tab[0], F_OK) == -1)
				return (g_status = 127, perror(data->cmd_tab[0]), -1);
			return (perror(data->cmd_tab[0]), -1);
		}
	}
	else if (!data->cmd_tab[0] && data->h_doc)
		return (-1);
	else
		if (exec_cmd(data->cmd_tab, data->envp, &adr))
			return (g_status = 127, -1);
	return (0);
}

void	child_killer(t_cmds *data, t_adr *adr, t_adr *perma, int status)
{
	if (data->pipe)
		close(data->pipe[1]);
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	data = data->first;
	free_all_node(data);
	clear_address(adr);
	clear_address(perma);
	rl_clear_history();
	exit(status);
}

static void	child(t_cmds *data, t_adr *adr, t_adr *perma)
{
	data->fd_in = 0;
	data->fd_out = 0;
	reset_signal();
	if (data->next)
		close(data->pipe[0]);
	if (data->h_doc)
	{
		if (data->prev_pipe)
			close(data->prev_pipe[0]);
	}
	if (redirect_control(data))
		child_killer(data, adr, perma, 1);
	if (prepare_exec(data, adr, perma))
		child_killer(data, adr, perma, g_status);
}

int	start_process(t_cmds *data, t_adr *adr, t_adr *perma)
{
	data->pipe = (int *)malloc(sizeof(int) * 2);
	if (!data->pipe)
		return (-1);
	append_node(&adr, data->pipe);
	if (pipe(data->pipe) == -1)
		return (-1);
	data->pid = fork();
	if (data->pid == -1)
		return (-1);
	if (!data->pid)
		child(data, adr, perma);
	if (data->h_doc)
		waitpid(data->pid, &g_status, 0);
	if (data->prev_pipe)
		close(data->prev_pipe[0]);
	if ((data->h_doc && g_status == 130))
		return (close(data->pipe[1]), close(data->pipe[0]), -1);
	return (data->next->prev_pipe = data->pipe, 0);
}

int	last_cmd(t_cmds *data, t_adr *adr, t_adr *perma)
{
	if (data->h_doc)
		if (check_heredoc(data))
			return (-1);
	data->pipe = NULL;
	data->pid = fork();
	if (data->pid == -1)
		return (-1);
	if (!data->pid)
		child(data, adr, perma);
	if (data->prev_pipe)
		close(data->prev_pipe[0]);
	return (0);
}
