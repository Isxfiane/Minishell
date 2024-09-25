/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:08:07 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 13:43:09 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	end_loop(t_cmds *data, t_cmds *first)
{
	data = first;
	while (data)
	{
		waitpid(data->pid, &g_status, 0);
		data = data->next;
	}
}

static void	set_firstnode(t_cmds *data, t_cmds *first)
{
	while (data)
	{
		data->first = first;
		data = data->next;
	}
	data = first;
}

void	cmd_loop(t_cmds *data, t_adr *adr, t_adr *perma)
{
	t_cmds	*first;

	data->status_set = 0;
	first = data;
	set_firstnode(data, first);
	if (init_env(data, adr, perma) || builtins_control(data, perma, adr))
		return ;
	data->prev_pipe = NULL;
	while (data->next)
	{
		if (data->h_doc)
			if (check_heredoc(data))
				return ;
		if (start_process(data, adr, perma))
			return ;
		if (data->pipe)
			close(data->pipe[1]);
		data = data->next;
	}
	if (last_cmd(data, adr, perma))
		return ;
	end_loop(data, first);
}
