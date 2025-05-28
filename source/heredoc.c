/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 04:31:33 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 15:53:39 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "environment.h"
#include "str.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>

char	*new_document(char *eof);
void	*pointer_storage(int type, void *ptr);
int	safe_fork();

static int	count_heredocs(t_token *tokens)
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

static char	**create_docs(t_token *tokens)
{
	char	**paths;
	char	*eof;
	int		count;
	int		i;
	
	count = count_heredocs(tokens);
	paths = (char **)gc_calloc((sizeof(char *) * (count + 1)), SECTION_LA);
	eof = NULL;
	i = -1;
	while (++i < count)
	{
		while ((tokens)->type != TOKEN_DLESS)
			tokens++;
		eof = (tokens + 1)->value;
		if (!eof)
		{
			printf("yosh: syntax error near unexpected token `newline'\n");
			exit(1);
		}
		paths[i] = new_document(eof);
		tokens++;
	}
	return (paths);
}

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
		buffer = ft_strjoin(buffer, reader_buffer, SECTION_ENV);
	}
	return (buffer);
}

static void	child_process(t_token *tokens, int pipe_fd[2])
{
	char	**buffer;
	int		i;
	
	close(pipe_fd[0]);
	buffer = create_docs(tokens);
	i = -1;
	while (buffer[++i])
	{
		write(pipe_fd[1], buffer[i], ft_strlen(buffer[i]));
		write(pipe_fd[1], "\n", 1);
	}
	close(pipe_fd[1]);
	exit(0);
}

static void	parent_process(t_token *tokens, int pipe_fd[2], pid_t pid)
{
	char	*pipe_buffer;
	
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	pipe_buffer = reader(pipe_fd[0]);
	char **splitted = ft_split(pipe_buffer, '\n', SECTION_LA);
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

int	expand_heredoc(t_token *tokens)
{
	pid_t	pid;
	int		pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
	{
		printf("pipe() failed: %d.\n", errno);
		exit(1);
	}
	pid = safe_fork();
	if (pid == 0)
		child_process(tokens, pipe_fd);
	else
		parent_process(tokens, pipe_fd, pid);
	return (0);
}
