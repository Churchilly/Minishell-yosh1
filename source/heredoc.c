/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 04:31:33 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/20 01:21:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "str.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include "minishell.h"
#include "heredoc.h"

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

static int	parent_process(t_token *tokens, int pipe_fd[2], pid_t pid)
{
	int		status;
	int		sig;

	close(pipe_fd[1]);
	status = 0;
	if (waitpid(pid, &status, 0) == -1)
	{
		printf("waitpid() failed: %d.\n", errno);
		exit(1);
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status != 0)
			return (update_last_pipe(status), 1);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (update_last_pipe(128 + sig), 1);
	}
	read_from_pipe(tokens, pipe_fd);
	return (0);
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
		if (parent_process(tokens, pipe_fd, pid))
			return (1);
	return (0);
}
