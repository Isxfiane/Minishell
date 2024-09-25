/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:32:45 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 15:22:33 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_strcmp_hdoc(char *hdoc, const char *s2)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = ft_strjoin(hdoc, "\n");
	if ((!s1 && s2) || (s1 && !s2))
		return (free(s1), 1);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (free(s1), 1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (free(s1), -1);
		i++;
	}
	if (s2[i])
		return (free(s1), -1);
	else if (s1[i])
		return (free(s1), 1);
	return (free(s1), 0);
}

static int	return_control(int tempfd, char *h_doc, char *line)
{
	if (g_status == 130)
	{
		free(line);
		close(tempfd);
		return (-1);
	}
	if (line == NULL)
	{
		free(line);
		printf("%s(wanted `%s')\n", EF, h_doc);
		close(tempfd);
		return (0);
	}
	free(line);
	close(tempfd);
	return (0);
}

int	start_heredoc(t_cmds *data)
{
	int		tempfd;
	char	*line;
	char	*h_doc;
	char	*new_line;

	g_status = 0;
	tempfd = open(".___tmpfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tempfd == -1)
		return (-1);
	h_doc = data->h_doc[ft_tablen(data->h_doc) - 1];
	line = NULL;
	while (1)
	{
		ft_printf_err("> ");
		line = get_next_line(0);
		if (!ft_strcmp_hdoc(h_doc, line) || !line || g_status == 130)
			break ;
		new_line = expand_hdoc(line, data);
		free(line);
		ft_putstr_fd(new_line, tempfd);
		free(new_line);
	}
	return (return_control(tempfd, h_doc, line));
}

int	check_heredoc(t_cmds *data)
{
	size_t	i;
	char	*h_doc;	
	char	*line;

	i = 0;
	line = NULL;
	while (i < ft_tablen(data->h_doc) - 1)
	{
		h_doc = data->h_doc[i];
		if (multi_hdoc_control(line, h_doc))
			return (-1);
		i++;
	}
	if (start_heredoc(data))
		return (-1);
	if (!data->cmd_tab || !data->next)
		return (0);
	return (0);
}

int	multi_hdoc_control(char *line, char *h_doc)
{
	g_status = 0;
	while (1)
	{
		ft_printf_err("> ");
		line = get_next_line(0);
		if (!ft_strcmp_hdoc(h_doc, line) || !line)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (g_status == 130)
		return (-1);
	if (!line)
		return (printf("%s(wanted `%s')\n", EF, h_doc), 0);
	return (0);
}
