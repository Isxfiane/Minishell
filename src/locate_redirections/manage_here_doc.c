/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:15 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/14 13:03:16 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_of_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

char	*skip_quotes(char *str, int *status)
{
	int		i;
	char	*result;
	int		j;

	i = 0;
	j = nb_of_quotes(str);
	if (j == 0)
		*status = 1;
	result = malloc(sizeof(char) * (ft_strlen(str) - j + 1));
	if (result == NULL)
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}

void	skip_whitespaces(char *line, int *i)
{
	while (is_charset(line[*i], "\f\t\n\r\v ") == -1)
		(*i)++;
}
