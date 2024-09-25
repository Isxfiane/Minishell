/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:46:18 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/05/31 14:14:33 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	end_builtin(t_cmds *data, t_adr *adr, t_adr *perma)
{
	free_all_node(data);
	clear_address(adr);
	clear_address(perma);
}

void	builtins_pwd(t_cmds *data, t_adr *adr, t_adr *perma)
{
	char	*dir;

	(void)data;
	dir = getcwd(NULL, 0);
	if (!dir)
		child_killer(data, adr, perma, 1);
	else
	{
		append_node(&adr, dir);
		ft_printf("%s\n", dir);
		end_builtin(data, adr, perma);
		exit(0);
	}
}
