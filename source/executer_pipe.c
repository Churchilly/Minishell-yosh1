/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:14:31 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 16:34:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"
#include "executer.h"

void	pipe_and_run(int *pipedes, t_astnode *node, int direction)
{
	close(pipedes[!direction]);
	dup2(pipedes[direction], direction);
	close(pipedes[direction]);
	if (direction)
	{
		if (node->left->type == NODE_PIPE)
			execute_pipe(node->left);
		else if (node->left->type == NODE_REDIRECT)
			execute_redirection(node->left);
		else
			execute_command(node->left);
	}
	else
	{
		if (node->right->type == NODE_PIPE)
			execute_pipe(node->right);
		else if (node->left->type == NODE_REDIRECT)
			execute_redirection(node->left);
		else
			execute_command(node->right);
	}
	exit(0);
}

void	execute_pipe(t_astnode *node)
{
	int		pipedes[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (!node || node->type != NODE_PIPE)
	{
		execute_command(node);
		return ;
	}
	if (pipe(pipedes) == -1)
	{
		printf("pipe() failed: %d.\n", errno);
		exit(1);
	}
	left_pid = safe_fork();
	if (left_pid == 0)
		pipe_and_run(pipedes, node, 1);
	right_pid = safe_fork();
	if (right_pid == 0)
		pipe_and_run(pipedes, node, 0);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
}
