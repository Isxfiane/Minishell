/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:50:00 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/10 12:50:05 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirec(t_split *split, unsigned int i, unsigned int k, unsigned int save)
{
	if (split->s[k + 1] == '<' || split->s[k + 1] == '>')
		k++;
	if (save != k && save != k - 1)
		split->result[i] = ft_substr(split->s, save, k - save);
	k = skip_redirection(split->s, k + 1, &split->mod);
	return (k);
}

int	check_spchar(t_split *sp, int k)
{
	if (is_charset(sp->s[k], sp->end) == -1)
		return (1);
	if (is_charset(sp->s[k], sp->str) == -1)
		return (1);
	if (is_charset(sp->s[k], "<>") == -1)
		return (1);
	return (0);
}

int	skip_charset(t_split *sp, int k)
{
	while (is_charset(sp->s[k], sp->str) == -1
		&& is_charset(sp->s[k], sp->end) != -1)
		k = k + check_mod(sp->s, &sp->mod, k);
	return (k);
}

void	init_split(t_split *split, char *s, char *str, char *end)
{
	split->s = s;
	split->str = str;
	split->end = end;
}

int	skip_word(t_split *sp, int i, int mod)
{
	while (!((is_charset(sp->s[i], sp->end) == -1
				|| is_charset(sp->s[i], sp->str) == -1)
			&& mod == 0) && sp->s[i] != '\0')
		i = i + check_mod(sp->s, &mod, i);
	return (i);
}
