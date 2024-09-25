/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:24:36 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/06 17:51:28 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_sorted_env(char **envp, t_adr *perma)
{
	char	**new_env;
	char	*tmp;
	int		i;
	int		j;

	new_env = ft_tabdup(envp, 0, perma);
	i = 0;
	while (new_env[i])
	{
		j = i + 1;
		tmp = new_env[i];
		while (new_env[j])
		{
			if (ft_strcmp(new_env[j], tmp) == -1)
			{
				tmp = new_env[j];
				new_env[j] = new_env[i];
				new_env[i] = tmp;
			}
			j++;
		}
		if (ft_strncmp(tmp, "_=", 2))
			ft_printf("declare -x %s\n", tmp);
		i++;
	}
}

static int	reset_value(t_cmds *data, char *arg, t_adr *perma)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (arg[j] != '=')
		j++;
	while (data->envp[i])
	{
		tmp = ft_substr(arg, 0, j + 1);
		if (!tmp)
			return (-1);
		if (ft_strnstr(data->envp[i], tmp, ft_strlen(data->envp[i])))
		{
			data->envp[i] = ft_strdup(arg);
			append_node(&perma, data->envp[i]);
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

int	add_to_env(t_cmds *data, char *arg, t_adr *perma)
{
	int		i;
	char	**new_envp;

	if (!ft_isalpha(arg[0]) || !ft_strchr(arg, '='))
		return (0);
	if (reset_value(data, arg, perma))
		return (0);
	i = ft_tablen(data->envp);
	new_envp = ft_tabdup(data->envp, 1, perma);
	if (!new_envp)
		return (-1);
	new_envp[i] = ft_strdup(arg);
	append_node(&perma, new_envp[i]);
	new_envp[i + 1] = (char *)malloc(1);
	if (!new_envp[i + 1])
		return (-1);
	append_node(&perma, new_envp[i + 1]);
	new_envp[i + 1] = NULL;
	data->envp = new_envp;
	return (0);
}

static int	check_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

void	builtins_export(t_cmds *data, t_adr *perma)
{
	int	i;

	i = 1;
	if (!data->cmd_tab[1])
		return (print_sorted_env(data->envp, perma));
	else
	{
		while (data->cmd_tab[i])
		{
			if (!ft_isalpha(data->cmd_tab[i][0])
			|| check_identifier(data->cmd_tab[i]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(data->cmd_tab[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				g_status = 1;
				i++;
			}
			else
			{
				add_to_env(data, data->cmd_tab[i], perma);
				i++;
			}
		}
	}
}
