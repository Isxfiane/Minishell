/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:57:31 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 12:25:31 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	trash_outfile(char *outfile)
{
	int	out;

	out = open(outfile, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (out == -1)
	{
		perror(outfile);
		return (-1);
	}
	close(out);
	return (0);
}

static int	trash_infile(char *infile, int type)
{
	int	in;

	if (type == 4)
		return (0);
	in = open(infile, O_RDONLY);
	if (in == -1)
	{
		g_status = 1;
		perror(infile);
		return (-1);
	}
	close(in);
	return (0);
}

int	set_stdin(t_cmds *data, char *infile, int type, int istrash)
{
	int	in;

	if (istrash)
		return (trash_infile(infile, type));
	if (infile)
	{
		if (type == 4)
			in = open (".___tmpfile", O_RDONLY);
		else
			in = open(infile, O_RDONLY);
		if (in == -1)
			return (g_status = 1, perror(infile), -1);
		data->fd_in = in;
		if (!data->cmd_tab[0] && data->pipe)
			return (close(data->pipe[1]), close(in), 0);
		dup2(in, 0);
	}
	else if (data->prev_pipe)
	{
		if (!data->h_doc)
			dup2(data->prev_pipe[0], 0);
		close(data->prev_pipe[0]);
	}
	return (0);
}

int	set_stdout(t_cmds *data, char *outfile, int mod, int istrash)
{
	int		out;

	if (istrash)
		return (trash_outfile(outfile));
	if (outfile)
	{
		if (mod == 3)
			out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (out == -1)
			return (perror(outfile), -1);
		data->fd_out = out;
		dup2(out, 1);
		if (data->pipe)
			return (close(data->pipe[0]), close(data->pipe[1]), 0);
	}
	else if (data->next)
	{
		dup2(data->pipe[1], 1);
		close(data->pipe[1]);
	}
	return (0);
}
