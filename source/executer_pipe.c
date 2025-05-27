/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:40:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/09 22:55:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int		safe_fork(void);
void	execute_command(t_astnode *node);

void	execute_pipe(t_astnode *node)
{
	int		pipedes[2];
	pid_t	pid;

	pipe(pipedes);
	pid = safe_fork();
	if (pid == 0)
	{
		close(pipedes[0]);
		dup2(pipedes[1], STDOUT_FILENO);
		if (node && node->left && node->left->type == NODE_PIPE)
			execute_pipe(node->left);
		else if (node && node->left && node->left->type == NODE_COMMAND)
			execute_command(node->left);
		close(pipedes[1]);
		exit(0);
	}
	close(pipedes[1]);
	dup2(pipedes[0], STDIN_FILENO);
	execute_command(node->right);
	close(pipedes[0]);
}
