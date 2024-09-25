/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:25:20 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/06 14:14:55 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_of_split(t_split *sp, unsigned int i, unsigned int count)
{
	count = 0;
	sp->mod = 0;
	while (sp->s[i] != '\0' && !((is_charset(sp->s[i], sp->end) == -1)
			&& sp->mod == 0))
	{
		i = skip_charset(sp, i);
		if ((sp->s[i] == '\0' || is_charset(sp->s[i], sp->end) == -1)
			&& count == 0)
			return (0);
		if (sp->s[i] == '<' || sp->s[i] == '>')
		{
			i = skip_redirection(sp->s, i + 1, &sp->mod);
			continue ;
		}
		i = skip_word(sp, i, sp->mod);
		if (((is_charset(sp->s[i - 1], sp->str) != -1) && sp->mod == 0)
			|| sp->s[i] == '\0')
			count++;
	}
	if (count == 0)
		return (1);
	return (count);
}

static char	*fill_result(char **res, char *s, unsigned int j, unsigned int k)
{
	char	*tmp;
	char	*tmp2;

	if (*res == 0)
		*res = ft_substr(s, j, k - j);
	else
	{
		tmp2 = ft_substr(s, j, k - j);
		tmp = ft_strjoin(*res, tmp2);
		free(tmp2);
		free(*res);
		*res = tmp;
	}
	if (*res == NULL)
		return (NULL);
	if (*res[0] == '\0')
	{
		free(*res);
		*res = NULL;
	}
	return (*res);
}

static char	**fillsplit(t_split *sp, unsigned int i, unsigned int k)
{
	unsigned int	save;

	sp->mod = 0;
	while (sp->s[k] != '\0' && !((is_charset(sp->s[k], sp->end) == -1)
			&& sp->mod == 0))
	{
		k = skip_charset(sp, k);
		save = k;
		if (sp->s[save] == '\0' || is_charset(sp->s[save], sp->end) == -1)
			break ;
		if (sp->s[k] == '<' || sp->s[k] == '>')
		{
			k = redirec(sp, i, k, save);
			continue ;
		}
		while (!(check_spchar(sp, k) == 1 && sp->mod == 0) && sp->s[k] != '\0')
			k = k + check_mod(sp->s, &sp->mod, k);
		sp->result[i] = fill_result(&sp->result[i], sp->s, save, k);
		i++;
	}
	if (i == 0 || sp->result[i - 1] != NULL)
		sp->result[i] = NULL;
	return (sp->result);
}

char	**spliter(char *s, char *str, char *end)
{
	unsigned int	n;
	char			**result;
	t_split			split;

	if (!s)
		return (NULL);
	init_split(&split, s, str, end);
	n = nb_of_split(&split, 0, 0);
	result = ft_calloc(n + 1, sizeof(char *));
	if (!result)
		return (NULL);
	split.result = result;
	if (s[0] == '\0')
	{
		result[0] = NULL;
		return (result);
	}
	return (fillsplit(&split, 0, 0));
}
