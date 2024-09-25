/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:53:38 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/10 13:46:10 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
			{
				if (line[i] == '\0')
					return (-1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

static int	check_pipe(char *line)
{
	int	i;
	int	mod;
	int	quotes;

	i = 0;
	mod = 0;
	quotes = 0;
	while (line[i] != '\0')
	{
		check_mod(line, &quotes, i);
		if (line[i] > 33 && line[i] != '|' && mod != 1)
			mod = 1;
		if (line[i] == '|' && quotes <= 0)
		{
			i++;
			if (line[i] == '|' || mod == 0)
				return (-1);
			if (skip_cmd(line, &i) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

static int	check_after_redir(char *line)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (line[i] != '\0')
	{
		check_mod(line, &quotes, i);
		if ((line[i] == '<' || line[i] == '>') && quotes <= 0)
		{
			if (line[i + 1] == line[i])
				i++;
			i++;
			while (line[i] != '\0' && is_charset(line[i], "\f\t\n\r\v ") == -1)
				i++;
			if (is_charset(line[i], "<>|") == -1 || line[i] == '\0')
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

static int	check_redirections(char *line)
{
	int		i;
	char	mod;
	int		quotes;

	i = 0;
	quotes = 0;
	while (line[i] != '\0')
	{
		check_mod(line, &quotes, i);
		if ((line[i] == '>' || line[i] == '<') && quotes <= 0)
		{
			mod = line[i];
			i++;
			if ((line[i] == '>' || line[i] == '<') && line[i] != mod)
				return (-1);
			if (line[++i] == '<' || line[i] == '>')
				return (-1);
			while (line[i] != '\0' && line[i] < 33)
				i++;
		}
		else
			i++;
	}
	return (0);
}

int	line_check(char *line)
{
	if (check_after_redir(line) == -1 || check_redirections(line) == -1)
	{
		ft_putstr_fd(RED"minishell: syntax error"
			"near unexpected token `newline`\n"RESET, 2);
		return (-1);
	}
	if (check_pipe(line) == -1)
	{
		ft_putstr_fd(RED"minishell: syntax error"
			"near unexpected token `|`\n"RESET, 2);
		return (-1);
	}
	if (check_quotes(line) == -1)
	{
		ft_putstr_fd(RED"minishell: unclosed quotes\n"RESET, 2);
		return (-1);
	}
	if (check_char(line, "[]{}()\\;&^%%#@*,:~") == -1)
	{
		ft_putstr_fd(RED"minishell: not interpret characters\n"RESET, 2);
		return (-1);
	}
	return (0);
}
