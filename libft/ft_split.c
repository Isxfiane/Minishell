/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:26:56 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/03/01 14:18:49 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	words_count(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			words++;
		}
	}
	return (words);
}

static char	**splitter(char const *s, char c, char **t)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (j < words_count(s, c))
	{
		start = 0;
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		t[j] = ft_substr(s, start, i - start);
		if (!t[j])
		{
			free_tab(t);
			return (NULL);
		}
		j++;
	}
	t[words_count(s, c)] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;

	t = malloc((words_count(s, c) + 1) * sizeof(char *));
	if (!s || !t)
		return (0);
	t = splitter(s, c, t);
	if (!t)
		return (NULL);
	return (t);
}
