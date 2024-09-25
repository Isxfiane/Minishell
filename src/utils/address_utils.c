/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:45:36 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/04 11:34:50 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstrm_addback(t_adr **li)
{
	t_adr	*temp;
	t_adr	*beforetemp;

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
	if (temp->address != NULL)
		free(temp->address);
	free(temp);
}

int	ft_lstadd_addback(t_adr **li, void *address)
{
	t_adr	*element;
	t_adr	*temp;

	element = malloc(sizeof(*element));
	if (!element)
		return (-1);
	element->address = address;
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

int	add_address(t_adr **li, void *address)
{
	if (address == NULL || ft_lstadd_addback(li, address) == -1)
	{
		clear_address(*li);
		return (-1);
	}
	return (0);
}

int	clear_address(t_adr *li)
{
	unlink(".___tmpfile");
	if (li == NULL)
		return (0);
	while (li->next != NULL)
		ft_lstrm_addback(&li);
	return (0);
}

void	free_all_node(t_cmds *info)
{
	while (info->next != NULL)
	{
		freetab(info->infile, 0);
		freetab(info->outfile, 0);
		freetab(info->h_doc, 0);
		clear_token(info->tok);
		info = info->next;
	}
	freetab(info->infile, 0);
	freetab(info->outfile, 0);
	freetab(info->h_doc, 0);
	clear_token(info->tok);
}
