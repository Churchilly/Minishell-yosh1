/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:41:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/30 19:22:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

void	execute_command(t_astnode *node);
static void	find_redirection_type(t_astnode *node, int red_to, int red_from);

static void	process_redirection(t_astnode *node, int red_to, int red_from, int fd)
{
	pid_t	pid;
	
	if (red_from == STDOUT_FILENO)
		red_from = fd;
	if (node->left && node->left->type == NODE_REDIRECT)
		find_redirection_type(node->left, red_to, red_from);
	else if (node->left && node->left->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(red_from, STDIN_FILENO);
			dup2(red_to, STDOUT_FILENO);
			close(red_from);
			close(red_to);
			execute_command(node->left);
		}
		else
		{
			close(red_from);
			close(red_to);
			waitpid(pid, NULL, 0);
		}
	}
}

static void	safe_open(int *fd, const char *__file, int __oflag)
{
	(*fd) = open(__file, __oflag, 0666);
	if ((*fd) == -1)
		exit(1);
}

static void	find_redirection_type(t_astnode *node, int red_to, int red_from)
{
	int		fd;

	if (!node)
		return ;
	if (node->redirect_type == TOKEN_GREAT)
	{
		safe_open(&fd, node->file, O_WRONLY | O_CREAT | O_TRUNC);
		process_redirection(node, red_to, red_from, fd);
	}
	else if (node->redirect_type == TOKEN_DGREAT)
	{
		safe_open(&fd, node->file, O_WRONLY | O_CREAT | O_APPEND);
		process_redirection(node, red_to, red_from, fd);
	}
	else if (node->redirect_type == TOKEN_LESS)
	{
		safe_open(&fd, node->file, O_RDONLY);
		process_redirection(node, red_to, red_from, fd);
	}
	exit(0);
}

void	execute_redirection(t_astnode *node)
{
	find_redirection_type(node, STDIN_FILENO, STDOUT_FILENO);
}
