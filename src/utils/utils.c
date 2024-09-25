/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:52:06 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/04 14:24:53 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_mod(char *line, int *mod, int i)
{
	if (line[i] == '$' && *mod != 2)
		i++;
	if (line[i] == '"')
	{
		if (*mod <= 0)
			*mod = 1;
		else if (*mod == 1)
			*mod = 0;
	}
	if (line[i] == '\'')
	{
		if (*mod <= 0)
			*mod = 2;
		else if (*mod == 2)
			*mod = 0;
	}
	if (line[i] == ' ')
	{
		if (*mod <= 0)
			*mod = 0;
	}
	return (1);
}

void	*freetab(char **result, int n)
{
	int	i;

	i = 0;
	if (result == NULL)
		return (NULL);
	if (n == 0)
	{
		while (result[i] != NULL)
		{
			free(result[i]);
			i++;
		}
	}
	else
	{
		while (n + 1 > i)
		{
			free(result[i]);
			i++;
		}
	}
	free(result);
	return (NULL);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	tab_real_len(char **tab)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
	{
		if (tab[i][0] != '\0')
			k++;
		i++;
	}
	return (k);
}

char	**dup_tab(char **tab, t_adr *adr)
{
	int		i;
	int		k;
	char	**new_tab;

	i = 0;
	k = tab_real_len(tab);
	new_tab = malloc(sizeof(char *) * (k + 1));
	if (add_address(&adr, new_tab) == -1)
		return (NULL);
	k = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] != '\0')
		{
			new_tab[k] = ft_strdup(tab[i]);
			if (add_address(&adr, new_tab[k]) == -1)
				return (NULL);
			k++;
		}
		i++;
	}
	new_tab[k] = NULL;
	freetab(tab, 0);
	return (new_tab);
}
