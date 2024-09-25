/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 07:05:58 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/15 22:51:49 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_args(t_expand *expand, int save, int j, int mod)
{
	char	*temp;
	char	*args;
	int		i;

	i = 0;
	temp = ft_substr(expand->line, save, j - save);
	if (temp == NULL)
		return (NULL);
	if (temp[0] == '?')
		args = ft_itoa(g_status);
	else
		args = ft_strdup(get_var(temp, expand->info));
	if (mod == 0 && args != NULL)
	{
		while (args[i] != '\0')
		{
			if (is_charset(args[i], "\f\t\n\r\v\"\' ") == -1)
				args[i] = args[i] * -1;
			i++;
		}
	}
	free(temp);
	return (args);
}

char	**extract_args(t_expand *expand, int mod)
{
	int		i;
	int		j;
	int		save;

	i = 0;
	j = 0;
	while (expand->line[j] != '\0')
	{
		check_mod(expand->line, &mod, j);
		if (expand->line[j] == '$' && mod != 2 && expand->line[j + 1] > 32
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

char	*place_args(t_expand *expand, int *i, int nb)
{
	int	j;

	j = 0;
	if (expand->args[nb] == NULL)
		return (expand->newline);
	while (expand->args[nb][j] != '\0')
	{
		expand->newline[*i] = expand->args[nb][j];
		j++;
		(*i)++;
	}
	return (expand->newline);
}

static char	*build_newline(t_expand *expand, int nb)
{
	int		i;
	int		j;
	int		mod;

	i = 0;
	j = 0;
	mod = 0;
	while (expand->line[j] != '\0' && i < expand->len)
	{
		check_mod(expand->line, &mod, j);
		if (expand->line[j] == '$' && (is_charset(expand->line[j + 1],
					"\f\t\n\r\v\'\" ") != -1 && mod != 2))
		{
			expand->newline = place_args(expand, &i, nb);
			nb++;
			j = skip_agrs(expand->line, j);
		}
		else if (check_quotes_mod(expand->line[j], mod) == 1)
			j++;
		else
			copy_char(expand->line, &j, &i, expand->newline);
	}
	expand->newline[i] = '\0';
	return (expand->newline);
}

char	*expand(char *line, t_cmds *info)
{
	t_expand	expand;
	int			x;

	init_expand(&expand, line, info);
	expand.count = count_args(expand.line);
	expand.args = malloc(sizeof(char *) * (expand.count + 1));
	if (expand.args == NULL)
		return (NULL);
	expand.args = extract_args(&expand, 0);
	if (expand.args == NULL)
		return (NULL);
	expand.len = expand.len + ft_strlen(line);
	x = count_quotes(line);
	expand.newline = malloc(sizeof(char) * (expand.len + 1 - x));
	if (expand.newline == NULL)
		return (freetab(expand.args, expand.count));
	build_newline(&expand, 0);
	freetab(expand.args, expand.count);
	return (expand.newline);
}
