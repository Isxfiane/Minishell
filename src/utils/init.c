/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:38:18 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/06 15:44:45 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmds(t_cmds *info, char **envp)
{
	info->envp = envp;
	info->tok = NULL;
	info->cmd_tab = NULL;
	info->infile = NULL;
	info->outfile = NULL;
	info->h_doc = NULL;
	info->next = NULL;
	info->here_doc_status = 0;
}

void	init_all(t_cmds *info, t_adr *adr)
{
	info->status_set = 0;
	info->cmd_tab = NULL;
	info->infile = NULL;
	info->outfile = NULL;
	info->h_doc = NULL;
	info->here_doc_status = 0;
	info->next = NULL;
	info->tok = NULL;
	adr->address = NULL;
	adr->next = NULL;
}

void	init_expand(t_expand *expand, char *line, t_cmds *info)
{
	expand->line = line;
	expand->newline = NULL;
	expand->args = NULL;
	expand->len = 0;
	expand->count = 0;
	expand->info = info;
}

void	init_perma(t_cmds *info, char **envp, t_adr *perma)
{
	g_status = 0;
	info->envp = envp;
	perma->address = NULL;
	perma->next = NULL;
}
