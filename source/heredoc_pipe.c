/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 14:40:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "str.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>

char	*reader(int fd)
{
	char	*buffer;
	char	reader_buffer[256];
	int		readen;

	buffer = ft_strdup("\0", SECTION_LA);
	readen = 1;
	while (readen)
	{
		readen = read(fd, reader_buffer, 256);
		if (readen == -1)
		{
			printf("read() failed: %d\n", errno);
			exit(1);
		}
		reader_buffer[readen] = '\0';
		buffer = ft_strjoin(buffer, reader_buffer, SECTION_LA);
	}
	return (buffer);
}

void	read_from_pipe(t_token *tokens, int pipe_fd[2])
{
	char	*pipe_buffer;
	char	**splitted;

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
