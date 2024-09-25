/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:37:41 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/10 13:46:02 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset(char s, char *charset)
{
	int	i;

	i = 0;
	if (s == '\0')
		return (-1);
	while (charset[i] != '\0')
	{
		if (s == charset[i])
			return (-1);
		i++;
	}
	return (0);
}

int	check_char(char *s, char *tofind)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'' )
		{
			quote = s[i];
			i++;
			while (s[i] != quote)
				i++;
		}
		else
		{
			if (is_charset(s[i], tofind) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	locate_char(char *s, char *tofind)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'' )
		{
			quote = s[i];
			i++;
			while (s[i] != quote)
				i++;
		}
		else
		{
			if (is_charset(s[i], tofind) == -1)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	check_whitespace(char *line)
{
	int	i;

	i = 0;
	while (is_charset(line[i], " \t\n\r\v\f") == -1)
	{
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	return (0);
}

int	skip_cmd(char *line, int *i)
{
	while (line[*i] < 33 && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (-1);
	return (0);
}
