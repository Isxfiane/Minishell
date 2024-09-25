/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:03:22 by sben-rho          #+#    #+#             */
/*   Updated: 2024/04/16 08:49:39 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_len(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[i] != NULL)
	{
		len = len + count_hiden_space(tab[i]) + 1;
		i++;
	}
	return (len);
}

static char	*sep(void)
{
	char	*result;

	result = malloc(sizeof(char) * 7);
	result[0] = -32;
	result[1] = -9;
	result[2] = -10;
	result[3] = -11;
	result[4] = -12;
	result[5] = -13;
	result[6] = '\0';
	return (result);
}

static void	fill_result(char **result, int *k, char *str)
{
	char	**tmp;
	int		j;
	char	*se;

	j = 0;
	se = sep();
	tmp = spliter(str, se, "");
	free(se);
	while (tmp[j] != NULL)
	{
		result[*k] = ft_strdup(tmp[j]);
		if (result[*k] == NULL)
			return ;
		j++;
		(*k)++;
	}
	freetab(tmp, 0);
}

char	**split_expand(char **tab)
{
	char	**result;
	int		i;
	int		k;

	k = calc_len(tab);
	result = malloc(sizeof(char *) * (k + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	k = 0;
	while (tab[++i] != NULL)
	{
		if (check_hiden_space(tab[i]) == 0)
		{
			result[k] = ft_strdup(tab[i]);
			if (result[k] == NULL)
				return (NULL);
			k++;
		}
		else
			fill_result(result, &k, tab[i]);
	}
	freetab(tab, 0);
	result[k] = NULL;
	return (result);
}
