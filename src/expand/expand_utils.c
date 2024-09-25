/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:20:38 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/10 13:10:49 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_mod(char c, int mod)
{
	if (c == '"' && mod != 2)
		return (1);
	if (c == '\'' && mod != 1)
		return (1);
	return (0);
}

int	count_args(char *line)
{
	int	i;
	int	mod;
	int	count;

	i = 0;
	mod = 0;
	count = 0;
	while (line[i] != '\0')
	{
		check_mod(line, &mod, i);
		if (line[i] == '$' && mod != 2
			&& is_charset(line[i + 1], "\f\t\n\r\v\'\" ") != -1)
		{
			if (line[i + 1] > 32)
				count++;
			i = skip_agrs(line, i);
		}
		else
			i++;
	}
	return (count);
}

void	copy_char(char *line, int *j, int *i, char *dest)
{
	int	mod;
	int	k;

	k = 0;
	mod = 0;
	while (k <= *j - 1)
	{
		check_mod(line, &mod, k);
		k++;
	}
	if (!(line[*j] == '$' && (line[*j + 1] == '\'' || line[*j + 1] == '\"')))
	{
		dest[*i] = line[*j];
		(*i)++;
	}
	else if (line[*j] == '$' && (line[*j + 1] == '\''
			|| line[*j + 1] == '\"') && mod != 0)
	{
		dest[*i] = line[*j];
		(*i)++;
	}
	(*j)++;
}

int	skip_agrs(char *line, int i)
{
	i++;
	if (line[i] == '$')
		return (i);
	if (line[i] == '?')
		return (i + 1);
	while ((ft_isalnum(line[i]) == 1 || line[i] == '_') && line[i] != '\0')
		i++;
	return (i);
}

int	count_quotes(char *line)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			count++;
			quote = line[i];
			i++;
			while (line[i] != quote && line[i] != '\0')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}
