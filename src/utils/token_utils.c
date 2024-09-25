/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:08:11 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/04 11:15:50 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstrm_tokback(t_token **li)
{
	t_token	*temp;
	t_token	*beforetemp;

	if (*li == NULL)
		return ;
	temp = *li;
	beforetemp = *li;
	while (temp->next != NULL)
	{
		beforetemp = temp;
		temp = temp->next;
	}
	beforetemp->next = NULL;
	if (temp->str != NULL)
		free(temp->str);
	free(temp);
}

int	ft_lstadd_tokback(t_token **li, int type, char *str)
{
	t_token	*element;
	t_token	*temp;

	element = malloc(sizeof(*element));
	if (!element)
		return (-1);
	element->type = type;
	element->str = str;
	element->next = NULL;
	if (*li == NULL)
	{
		*li = element;
		return (0);
	}
	temp = *li;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = element;
	return (0);
}

int	clear_token(t_token *li)
{
	if (li == NULL)
		return (0);
	while (li->next != NULL)
		ft_lstrm_tokback(&li);
	ft_lstrm_tokback(&li);
	return (0);
}
