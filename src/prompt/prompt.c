/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:12:26 by sben-rho          #+#    #+#             */
/*   Updated: 2024/05/26 19:04:26 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*cwd;
	char	*result;
	char	*home;
	char	*tmp;
	size_t	len;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (cwd == NULL || home == NULL)
		return (NULL);
	len = ft_strlen(home);
	result = ft_strnstr(cwd, home, ft_strlen(cwd));
	if (result == NULL)
		return (cwd);
	tmp = ft_substr(cwd, len, ft_strlen(cwd) + len);
	if (tmp == NULL)
		return (NULL);
	free(result);
	result = tmp;
	if (result[0] == '\0')
		result = replace(result, "~");
	return (result);
}

static char	*build_pwd(char *pwd)
{
	pwd = add_char_start(pwd, BCYN"["RESET);
	if (pwd == NULL)
		return (NULL);
	pwd = add_char_end(pwd, BCYN"]"RESET);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}

static char	*build_user(char *user)
{
	user = add_char_start(user, CYN"┌──"BCYN"("BGRN);
	if (user == NULL)
		return (NULL);
	user = add_char_end(user, BCYN")-"RESET);
	if (user == NULL)
		return (NULL);
	return (user);
}

static char	*build_line(char *result)
{
	char	*tmp;
	char	*newline;

	newline = ft_strdup(CYN"\n└─"BGRN"$ "RESET);
	if (newline == NULL)
		return (ft_strdup("Minishell $ "));
	tmp = ft_strjoin(result, newline);
	if (tmp == NULL)
		return (ft_strdup("Minishell $ "));
	free(result);
	result = tmp;
	free(newline);
	return (result);
}

char	*get_prompt(void)
{
	char	*pwd;
	char	*user;
	char	*result;

	pwd = get_pwd();
	user = ft_strdup(getenv("USER"));
	if (pwd == NULL || user == NULL)
		return (ft_strdup("Minishell $ "));
	pwd = build_pwd(pwd);
	user = build_user(user);
	if (pwd == NULL || user == NULL)
		return (ft_strdup("Minishell $ "));
	result = ft_strjoin(user, pwd);
	free(pwd);
	free(user);
	if (result == NULL)
		return (ft_strdup("Minishell $ "));
	return (build_line(result));
}
