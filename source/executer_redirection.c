/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:41:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:16:58 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "minishell.h"
#include "executer.h"

static void	find_redirection_type(t_astnode *node, int red_to, int red_from);

void	create_dup(int red_to, int red_from)
{
	if (red_from != STDIN_FILENO)
		dup2(red_from, STDIN_FILENO);
	if (red_to != STDOUT_FILENO)
		dup2(red_to, STDOUT_FILENO);
}

static void	process_redirection(t_astnode *node, int red_to, int red_from)
{
	pid_t	pid;
	char	*path;

	if (node->left && node->left->type == NODE_REDIRECT)
		find_redirection_type(node->left, red_to, red_from);
	else if (node->left && node->left->type == NODE_COMMAND)
	{
		pid = safe_fork();
		if (pid == 0)
		{
			path = search_executable_path(node->left->args[0]);
			if (!path)
			{
				printf("%s: command not found\n", *(node->left->args));
				exit(1);
			}
			create_dup(red_to, red_from);
			execute_command(node->left);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}

static void	safe_open(int *fd, int *red, const char *__file, int __oflag)
{
	(*fd) = open(__file, __oflag, 0666);
	if ((*fd) == -1)
	{
		printf("open() failed: %d.\n", errno);
		exit(1);
	}
	if ((*red) == STDIN_FILENO || (*red) == STDOUT_FILENO)
		(*red) = (*fd);
}

static void	find_redirection_type(t_astnode *node, int red_to, int red_from)
{
	int		fd;

	if (!node)
		return ;
	if (node->redirect_type == TOKEN_GREAT)
	{
		safe_open(&fd, &red_to, node->file, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (node->redirect_type == TOKEN_DGREAT)
	{
		safe_open(&fd, &red_to, node->file, O_WRONLY | O_CREAT | O_APPEND);
	}
	else if (node->redirect_type == TOKEN_LESS)
	{
		safe_open(&fd, &red_from, node->file, O_RDONLY);
	}
	process_redirection(node, red_to, red_from);
	close(fd);
}

void	execute_redirection(t_astnode *node)
{
	find_redirection_type(node, STDOUT_FILENO, STDIN_FILENO);
}
