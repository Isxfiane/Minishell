/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:09:28 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/04 13:58:32 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirection(char *str, int i, int *mod)
{
	char	*result;
	int		save;
	char	tmp;

	while (is_charset(str[i], "\f\t\n\r\v ") == -1)
		i++;
	if (str[i] == '\0')
		return (NULL);
	save = i;
	check_mod(str, mod, i);
	while (ft_isprint(str[i]) == 1
		&& (is_charset(str[i], "|<> ") != -1) && mod != 0)
	{
		check_mod(str, mod, i);
		if (str[i] == '"' || str[i] == '\'')
		{
			tmp = str[i];
			i++;
			while (str[i] != '\0' && str[i] != tmp)
				i = i + check_mod(str, mod, i);
		}
		i++;
	}
	result = ft_substr(str, save, i - save);
	return (result);
}

int	skip_redirection(char *line, int i, int *mod)
{
	char	tmp;

	while (is_charset(line[i], "\f\t\n\r\v ") == -1)
		i++;
	if (line[i] == '\0')
		return (-1);
	while (ft_isprint(line[i]) == 1
		&& (is_charset(line[i], "|<> ") != -1) && mod != 0)
	{
		check_mod(line, mod, i);
		if (line[i] == '"' || line[i] == '\'')
		{
			tmp = line[i];
			i++;
			while (line[i] != '\0' && line[i] != tmp)
				i = i + check_mod(line, mod, i);
		}
		if (line[i] != '\0' && is_charset(line[i], "|<> ") != -1)
			i = i + check_mod(line, mod, i);
	}
	if (line[i] != '\0' && is_charset(line[i], "\f\t\n\r\v<>| ") != -1)
		i = i + check_mod(line, mod, i);
	return (i);
}

int	choose_case(t_cmds *info, int *i, int *mod)
{
	int	status;

	if (info->line[(*i) + 1] == '<')
		status = h_doc_case(info, i, mod);
	else
		status = infile_case(info, i, mod);
	return (status);
}

int	locate_infile_start(t_cmds *info)
{
	int	i;
	int	mod;
	int	status;

	i = 0;
	mod = 0;
	status = 0;
	skip_whitespaces(info->line, &i);
	while (info->line[i] != '\0' && info->line[i] != '|'
		&& (is_charset(info->line[i], "><") == -1 && info->line[i] > 33))
	{
		check_mod(info->line, &mod, i);
		if (info->line[i] == '<' && mod == 0)
			status = choose_case(info, &i, &mod);
		else if (info->line[i] == '>' && mod == 0)
			status = outfile_case(info, &i, &mod);
		else
			i++;
		if (status == -1)
			return (-1);
	}
	return (i);
}

int	locate_redirection_end(t_cmds *info)
{
	int	mod;
	int	i;
	int	status;

	i = 0;
	mod = 0;
	status = 0;
	while (info->line[i] != '\0' && (info->line[i] != '|' || mod != 0))
	{
		check_mod(info->line, &mod, i);
		if (info->line[i] == '<' && mod == 0)
			status = choose_case(info, &i, &mod);
		else if (info->line[i] == '>' && mod == 0)
			status = outfile_case(info, &i, &mod);
		else
			i++;
		if (status == -1)
			return (-1);
	}
	return (0);
}
