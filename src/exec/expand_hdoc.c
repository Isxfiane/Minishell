/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:40:24 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/10 09:51:08 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_new_line(t_expand *expand)
{
	int		i;
	int		j;
	int		mod;
	int		nb;

	i = 0;
	j = 0;
	nb = 0;
	mod = 0;
	while (expand->line[j] != '\0' && i < expand->len)
	{
		check_mod(expand->line, &mod, j);
		if (expand->line[j] == '$' && is_charset(expand->line[j + 1],
				"\f\t\n\r\v\'\" ") != -1)
		{
			expand->newline = place_args(expand, &i, nb);
			nb++;
			j = skip_agrs(expand->line, j);
		}
		else
			copy_char(expand->line, &j, &i, expand->newline);
	}
	expand->newline[i] = '\0';
	return (expand->newline);
}

static char	**extract_all_args(t_expand *expand, int mod)
{
	int		i;
	int		j;
	int		save;

	i = 0;
	j = 0;
	while (expand->line[j] != '\0')
	{
		check_mod(expand->line, &mod, j);
		if (expand->line[j] == '$' && expand->line[j + 1] > 32
			&& is_charset(expand->line[j + 1], "\f\t\n\r\v\"\' ") != -1)
		{
			save = j + 1;
			j = skip_agrs(expand->line, j);
			expand->args[i] = get_args(expand, save, j, mod);
			if (errno == ENOMEM)
				return (freetab(expand->args, i));
			expand->len = expand->len + ft_strlen(expand->args[i]) - (j - save);
			i++;
		}
		else
			j++;
	}
	expand->args[i] = NULL;
	return (expand->args);
}

static int	count_all_args(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && is_charset(line[i + 1], "\f\t\n\r\v\'\" ") != -1)
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

char	*expand_hdoc(char *line, t_cmds *info)
{
	t_expand	expand;

	init_expand(&expand, line, info);
	expand.count = count_all_args(expand.line);
	expand.args = malloc(sizeof(char *) * (expand.count + 1));
	if (expand.args == NULL)
		return (NULL);
	expand.args = extract_all_args(&expand, 0);
	if (expand.args == NULL)
		return (NULL);
	expand.len = expand.len + ft_strlen(line);
	expand.newline = malloc(sizeof(char) * (expand.len + 1));
	if (expand.newline == NULL)
		return (freetab(expand.args, expand.count));
	fill_new_line(&expand);
	freetab(expand.args, expand.count);
	return (expand.newline);
}
