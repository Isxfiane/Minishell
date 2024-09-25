/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:03:05 by sben-rho          #+#    #+#             */
/*   Updated: 2024/04/16 09:17:21 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_back(t_cmds **li, char **envp, t_adr *adr)
{
	t_cmds	*element;
	t_cmds	*temp;

	element = malloc(sizeof(*element));
	if (add_address(&adr, element) == -1)
		return (-1);
	init_cmds(element, envp);
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

void	fix_status(void)
{
	wait(&g_status);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
		g_status = 128 + WTERMSIG(g_status);
}

void	clear_all(t_adr perma)
{
	ft_printf("exiting ...\n");
	clear_address(&perma);
	rl_clear_history();
	exit(0);
}
