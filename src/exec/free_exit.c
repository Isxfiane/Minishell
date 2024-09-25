/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:52:06 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/06 14:58:11 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_adr	*get_lastnode(t_adr *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

int	append_node(t_adr **list, void *address)
{
	t_adr	*node;
	t_adr	*last;

	node = (t_adr *)malloc(sizeof(t_adr));
	if (!node)
		return (-1);
	node->next = NULL;
	node->address = address;
	if (!*list)
		*list = node;
	else
	{
		last = get_lastnode(*list);
		last->next = node;
	}
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
