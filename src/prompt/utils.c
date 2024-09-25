/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:35:55 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/25 12:36:06 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char_start(char *str, char *add)
{
	char	*tmp;

	tmp = ft_strjoin(add, str);
	if (tmp == NULL)
		return (NULL);
	free(str);
	str = tmp;
	return (str);
}

char	*add_char_end(char *str, char *add)
{
	char	*tmp;

	tmp = ft_strjoin(str, add);
	if (tmp == NULL)
		return (NULL);
	free(str);
	str = tmp;
	return (str);
}

char	*replace(char *str, char *src)
{
	free(str);
	str = ft_strdup(src);
	if (str == NULL)
		return (NULL);
	return (str);
}
