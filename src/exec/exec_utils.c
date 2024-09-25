/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:13:18 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 14:22:42 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_allpaths(char **envp, t_adr **address)
{
	char	*raw_paths;
	char	**paths;
	int		i;

	i = 0;
	if (!envp)
		return (ft_split(" ", ' '));
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_split(" ", ' '));
	raw_paths = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!raw_paths)
		return (NULL);
	append_node(address, raw_paths);
	paths = ft_split(raw_paths, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*get_cmdpath(char *cmd, char **envp, t_adr **address)
{
	char	*tmp;
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	all_paths = get_allpaths(envp, address);
	if (!all_paths)
		return (NULL);
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		if (!tmp)
			return (free_tab(all_paths), NULL);
		path = ft_strjoin(tmp, cmd);
		if (!path)
			return (free_tab(all_paths), free(tmp), NULL);
		free(tmp);
		if (!access(path, F_OK | X_OK))
			return (free_tab(all_paths), path);
		free(path);
		i++;
	}
	path = ft_strdup("");
	return (free_tab(all_paths), path);
}

int	exec_cmd(char **cmd_tab, char **envp, t_adr **address)
{
	char	*path;

	if (cmd_tab[0] == NULL)
		return (ft_printf_err("''%s\n", CMD_ERR));
	path = get_cmdpath(cmd_tab[0], envp, address);
	if (!path)
		return (-1);
	if (execve(path, cmd_tab, envp) == -1)
	{
		ft_putstr_fd(cmd_tab[0], 2);
		ft_putendl_fd(CMD_ERR, 2);
		free(path);
		return (-1);
	}
	return (0);
}

static int	trash_redirect(t_token *tok, int type)
{
	if (!tok)
		return (0);
	while (tok)
	{
		if (tok->type == type)
			return (1);
		tok = tok->next;
	}
	return (0);
}

int	redirect_control(t_cmds *data)
{
	t_token	*tok;
	int		is_trash;

	tok = data->tok;
	if (!trash_redirect(tok, 1) || !trash_redirect(tok, 4))
		set_stdin(data, NULL, 0, 0);
	if (!trash_redirect(tok, 2) || !trash_redirect(tok, 3))
		set_stdout(data, NULL, 0, 0);
	while (tok)
	{
		is_trash = trash_redirect(tok->next, 1) + trash_redirect(tok->next, 4);
		if (tok->type == 1 || tok->type == 4)
			if (set_stdin(data, tok->str, tok->type, is_trash))
				return (-1);
		is_trash = trash_redirect(tok->next, 2) + trash_redirect(tok->next, 3);
		if (tok->type == 2 || tok->type == 3)
			if (set_stdout(data, tok->str, tok->type, is_trash))
				return (-1);
		tok = tok->next;
	}
	return (0);
}
