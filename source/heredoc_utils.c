/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:37:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/11 22:00:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_strjoin_nl(char const *s1, char const *s2)
{
	int	s1_len;
	int	s2_len;
	char	*final_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_string = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!final_string)
		return (NULL);
	ft_memcpy(final_string, s1, s1_len);
	ft_memcpy(final_string + s1_len, s2, s2_len);
	final_string[s1_len + s2_len] = '\n';
	final_string[s1_len + s2_len + 1] = '\0';
	return (final_string);
}

int	is_alpha_numerical(char c)
{
	return ((c <= '9' && c >= '0')
		|| (c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A'));
}

void	*free_docs(char **docs)
{
	int	i;

	i = -1;
	while (docs[++i])
		free(docs[i]);
	free(docs);
	return (NULL);
}