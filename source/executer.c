/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/05/31 14:46:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include "environment.h"
#include <stdlib.h>
#include <fcntl.h>

void	execute_pipe(t_astnode *node);
void	execute_redirection(t_astnode *node);
void	execute_command(t_astnode *node);
void	update_last_pipe(int status);
void	*pointer_storage(int type, void *ptr);
int setup_child_signals(void);
int	is_builtin(char *command);

static int	safe_fork()
{
	t_garbage_collector	*gc;
	pid_t				pid;
	
	pid = fork();
	if (pid == -1)
	{
		printf("fork() failed: %d.\n", errno);
		exit(1);
	}
	gc = pointer_storage(COLLECTOR, NULL);
 	if (pid == 0)
	{
		gc->in_fork = 1;
	}
	return (pid);
}

static int	execute_valid_tree(void (*execute_func)(t_astnode *),
		t_astnode *node)
{
	pid_t	pid;
	int		status;
	
	if (node->type == NODE_COMMAND && is_builtin(node->args[0]))
	{
		execute_func(node);
		return (0);
	}
	pid = safe_fork();
	if (pid == 0)
	{
		execute_func(node);
		exit(0);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			printf("waitpid() failed: %d.\n", errno);
			exit(1);
		}
		if ( WIFEXITED(status) )
			status = WEXITSTATUS(status);
		update_last_pipe(status);
	}
	return (0);
}

// returns 0 on success
// returns 1 on error
void	executer(t_astnode *root)
{
	setup_child_signals();
	if (root->type == NODE_PIPE)
		execute_valid_tree(execute_pipe, root);
	else if (root->type == NODE_REDIRECT)
		execute_valid_tree(execute_redirection, root);
	else if (root->type == NODE_COMMAND)
		execute_valid_tree(execute_command, root);
}
