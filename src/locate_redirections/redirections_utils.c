/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:04 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/06 14:13:17 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab != NULL && tab[i] != NULL)
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (new_tab[i] == NULL)
			return (freetab(new_tab, i));
		i++;
	}
	new_tab[i + 1] = NULL;
	freetab(tab, 0);
	return (new_tab);
}

int	h_doc_case(t_cmds *info, int *i, int *mod)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	len = tab_len(info->h_doc);
	info->h_doc = update_tab(info->h_doc);
	*i = *i + 2;
	tmp = get_redirection(info->line, *i, mod);
	if (tmp == NULL)
		return (-1);
	*i = skip_redirection(info->line, *i, mod);
	info->here_doc_status = 0;
	tmp2 = skip_quotes(tmp, &info->here_doc_status);
	info->h_doc[len] = ft_strdup(tmp2);
	ft_lstadd_tokback(&info->tok, 4, tmp2);
	free(tmp);
	return (0);
}

int	infile_case(t_cmds *info, int *i, int *mod)
{
	char	*tmp;
	char	*tmp2;

	*i = *i + 1;
	tmp = get_redirection(info->line, *i, mod);
	if (tmp == NULL)
		return (-1);
	tmp2 = expand(tmp, info);
	*i = skip_redirection(info->line, *i, mod);
	ft_lstadd_tokback(&info->tok, 1, tmp2);
	free(tmp);
	return (0);
}

int	outfile_case(t_cmds *info, int *i, int *mod)
{
	char	*tmp;
	char	*tmp2;
	int		out;

	out = out_mod_case(info->line, i);
	*i = *i + 1;
	tmp = get_redirection(info->line, *i, mod);
	if (tmp == NULL)
		return (-1);
	tmp2 = expand(tmp, info);
	free(tmp);
	if (tmp2 == NULL)
		return (-1);
	if (tmp2[0] == '\0')
	{
		ft_putstr_fd(RED"minishell: ambiguous redirect\n"RESET, 2);
		return (-1);
	}
	*i = skip_redirection(info->line, *i, mod);
	if (out == 1)
		ft_lstadd_tokback(&info->tok, 3, tmp2);
	else
		ft_lstadd_tokback(&info->tok, 2, tmp2);
	return (0);
}

int	out_mod_case(char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}
