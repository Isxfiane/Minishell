/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:53:37 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/03 08:52:50 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	str_isnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	builtins_exit(t_cmds *data, t_adr *adr, t_adr *perma)
{
	g_status = 0;
	ft_putendl_fd("exit", 1);
	if (!data->envp[0])
		printf("Environement not set\n");
	else if (data->cmd_tab[1] && data->cmd_tab[1][0] != '-'
	&& data->cmd_tab[1][0] != '+' && !str_isnum(data->cmd_tab[1]))
	{
		g_status = 2;
		ft_putstr_fd(data->cmd_tab[0], 2);
		ft_putendl_fd(NUM_ERR, 2);
	}
	else if (data->cmd_tab[1] != NULL && data->cmd_tab[2])
	{
		g_status = 1;
		ft_putstr_fd(data->cmd_tab[0], 2);
		ft_putendl_fd(ARG_ERR, 2);
		return ;
	}
	else if (data->cmd_tab[1])
		g_status = (ft_atoi(data->cmd_tab[1]) % 256);
	free_all_node(data);
	clear_address(adr);
	clear_address(perma);
	rl_clear_history();
	exit(g_status);
}
