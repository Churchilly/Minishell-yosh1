/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/04/30 19:17:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executer.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include "enviroment.h"
#include <stdlib.h>
#include <fcntl.h>


void	execute_pipe(t_astnode *node);
void	execute_redirection(t_astnode *node);
void	execute_command(t_astnode *node);

extern char **__environ;

// 3 -> systemcall error
// 2 -> execution error
// 1 -> no node
static void	execute_valid_tree(void (*execute_func)(t_astnode *), t_astnode *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1); // error handling
	if (pid == 0)
		execute_func(node);
	else
		waitpid(pid, NULL, 0);
}

// returns 0 on success
// returns 1 on error
void	executer(t_astnode *root)
{
	if (root->type == NODE_PIPE)
		execute_valid_tree(execute_pipe, root);
	else if (root->type == NODE_REDIRECT)
		execute_valid_tree(execute_redirection, root);
	else
		execute_valid_tree(execute_command, root);
}
