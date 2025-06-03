/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:09 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 14:37:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	int		on_word;

	i = 0;
	on_word = 0;
	while (*s)
	{
		if (*s != c && !on_word)
		{
			on_word = 1;
			i++;
		}
		else if (*s == c && on_word)
			on_word = 0;
		s++;
	}
	return (i);
}

static char	*ft_word_dup(const char *s, size_t size, t_section sec)
{
	char	*dup;
	size_t	i;

	dup = (char *)gc_calloc(sizeof(char) * size + 1, sec);
	i = 0;
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int	ft_split_words(char **split, const char *s, char c, t_section sec)
{
	const char	*p;
	size_t		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			p = s;
			while (*s && *s != c)
				s++;
			split[i] = ft_word_dup(p, s - p, sec);
			i++;
		}
		if (*s)
			s++;
	}
	split[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c, t_section section)
{
	char	**split;

	if (!s)
		exit(1);
	split = (char **)gc_calloc(sizeof(char *) * (ft_count_words(s, c) + 1),
			section);
	ft_split_words(split, s, c, section);
	return (split);
}
