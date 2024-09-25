/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:45:39 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/10 15:27:48 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

int	build_cmd_tab(t_cmds *info, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	info->cmd_tab = spliter(line, "\f\t\n\r\v ", "|");
	if (info->cmd_tab == NULL)
		return (-1);
	while (info->cmd_tab[i] != NULL)
	{
		tmp = expand(info->cmd_tab[i], info);
		if (tmp == NULL)
			return (-1);
		free(info->cmd_tab[i]);
		info->cmd_tab[i] = tmp;
		i++;
	}
	info->cmd_tab = split_expand(info->cmd_tab);
	if (info->cmd_tab == NULL)
		return (-1);
	return (0);
}
int	parser(t_cmds *info, t_adr *adr);

int	next_pipe(t_cmds *info, t_adr *adr, int j)
{
	char	*tmp;

	ft_lstadd_back(&info, info->envp, adr);
	tmp = ft_strdup(&info->line[j + 1]);
	if (tmp == NULL)
		return (-1);
	info = info->next;
	init_cmds(info, info->envp);
	info->line = tmp;
	if (add_address(&adr, info->line) == -1)
		return (-1);
	if (parser(info, adr) == -1)
		return (-1);
	return (0);
}

int	parser(t_cmds *info, t_adr *adr)
{
	int		j;

	j = locate_infile_start(info);
	if (j == -1)
		return (-1);
	info->line = ft_strdup(&info->line[j]);
	if (add_address(&adr, info->line) == -1)
		return (-1);
	if (info->line == NULL)
		return (-1);
	if (build_cmd_tab(info, info->line) == -1)
		return (-1);
	info->cmd_tab = dup_tab(info->cmd_tab, adr);
	if (locate_redirection_end(info) == -1)
		return (-1);
	j = locate_char(info->line, "|");
	if (j == -1)
	{
		info->next = NULL;
		return (0);
	}
	if (next_pipe(info, adr, j) == -1)
		return (-1);
	return (0);
}

int	parsing(t_cmds *info, t_adr *adr)
{
	if (!info->line || info->line[0] == '\0'
		|| check_whitespace(info->line) == -1)
		return (-1);
	add_history(info->line);
	if (line_check(info->line) == -1)
		return (-1);
	if (ft_lstadd_addback(&adr, NULL) == -1)
		return (-1);
	if (parser(info, adr) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	info;
	t_adr	adr;
	t_adr	perma;
	char	*prompt;

	(void)argc;
	(void)argv;
	init_perma(&info, envp, &perma);
	while (1)
	{
		init_signal();
		init_all(&info, &adr);
		prompt = get_prompt();
		info.line = readline(prompt);
		free(prompt);
		if (!info.line)
			break ;
		if (parsing(&info, &adr) == 0)
			cmd_loop(&info, &adr, &perma);
		free_all_node(&info);
		clear_address(&adr);
		if (!info.status_set)
			fix_status();
	}
	clear_all(perma);
}
