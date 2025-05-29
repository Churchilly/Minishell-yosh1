/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:40:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 17:56:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int		safe_fork(void);
void	execute_command(t_astnode *node);
void	execute_pipe(t_astnode *node);

void	pipe_child(t_astnode *node, int pipedes[2])
{
	close(pipedes[0]);
	dup2(pipedes[1], STDOUT_FILENO);
	close(pipedes[1]);
	execute_pipe(node->left);
	exit(0);
}

void	execute_pipe(t_astnode *node)
{
	int		pipedes[2];
	pid_t	pid;

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
	pid = safe_fork();
	if (pid == 0) // childprocess
	{
		close(pipedes[1]);
		dup2(pipedes[0], STDIN_FILENO);
		close(pipedes[0]);
		execute_command(node->right);
		waitpid(pid, NULL, 0);
	}
	else
		pipe_child(node, pipedes);

}
