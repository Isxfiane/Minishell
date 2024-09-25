/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:39:53 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/05/28 15:14:01 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*freeall(char *temp)
{
	free(temp);
	return (NULL);
}

static char	*save_result(char *result)
{
	char	*temp;

	temp = ft_strdup(result);
	free(result);
	if (!temp)
		return (NULL);
	return (temp);
}

static char	*fusion(char *buffer, char *result, ssize_t lenread, int *n)
{
	char	*temp;
	int		i;

	i = ft_strfind(buffer, '\n');
	if (lenread != BUFFER_SIZE || i != -1)
		*n = -1;
	temp = save_result(result);
	if (i != -1)
	{
		result = (char *) malloc ((sizeof(char) * i)
				+ (sizeof(char) * ft_strlen(temp)) + 2);
		if (!result)
			return (freeall(temp));
		result = ft_str2cpy(temp, buffer, result, i + 1);
	}
	else
	{
		result = (char *) malloc ((sizeof(char) * lenread)
				+ (sizeof(char) * ft_strlen(temp)) + 1);
		if (!result)
			return (freeall(temp));
		result = ft_str2cpy(temp, buffer, result, lenread);
	}
	free(temp);
	return (result);
}

static char	*save(char *buffer, char *result, ssize_t lenread, int *n)
{
	int	i;
	int	j;

	if (buffer[0] != '\0')
	{
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n' && buffer[i + 1] != '\0')
		{
			j = 0;
			i++;
			while (buffer[i])
				buffer[j++] = buffer[i++];
			buffer[j] = '\0';
			result = fusion(buffer, result, lenread, n);
		}
		else
			result = NULL;
	}
	else
		return (NULL);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;
	int			n;
	ssize_t		lenread;

	n = 0;
	lenread = BUFFER_SIZE;
	result = NULL;
	if (ft_strfind(buffer, '\n') != -1)
		result = save(buffer, result, lenread, &n);
	while (n != -1)
	{
		lenread = read(fd, buffer, BUFFER_SIZE);
		buffer[lenread] = '\0';
		if (lenread == 0)
			return (result);
		if (lenread == -1)
		{
			free(result);
			return (NULL);
		}
		result = fusion(buffer, result, lenread, &n);
	}
	return (result);
}
