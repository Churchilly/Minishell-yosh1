/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:37:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/02 16:27:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <unistd.h>
#include "garbage_collector.h"
#include "lexer.h"

char	*ft_strjoin_nl(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*final_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_string = gc_calloc(sizeof(char) * (s1_len + s2_len + 2), SECTION_LA);
	ft_memcpy(final_string, s1, s1_len);
	ft_memcpy(final_string + s1_len, s2, s2_len);
	final_string[s1_len + s2_len] = '\n';
	final_string[s1_len + s2_len + 1] = '\0';
	return (final_string);
}

int	count_heredocs(t_token *tokens)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	while (tokens[++i].value)
	{
		if (tokens[i].type == TOKEN_DLESS)
			ret++;
	}
	return (ret);
}

void	parent_process_helper(t_token *tokens, char **splitted,
			char *pipe_buffer, int *pipe_fd)
{
	pipe_buffer = reader(pipe_fd[0]);
	splitted = ft_split(pipe_buffer, '\n', SECTION_LA);
	while (*splitted)
	{
		while (tokens->type != TOKEN_DLESS)
			tokens++;
		tokens->type = TOKEN_LESS;
		tokens->value = ft_strdup("<", SECTION_LA);
		tokens++;
		tokens->value = *splitted;
		gc_add(tokens->value, SECTION_PATHS);
		splitted++;
	}
}
