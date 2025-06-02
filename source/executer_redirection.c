/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:41:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/02 16:26:36 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int			safe_fork(void);
void		execute_command(t_astnode *node);
static void	find_redirection_type(t_astnode *node, int red_to, int red_from);
char		*search_executable_path(char *file_path);

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

void print_open_error(int status, const char *dir)
{
	if (status == ENOENT)
		printf("yosh1: %s: No such file or directory\n", dir);
	else if (status == ENOTDIR)
		printf("yosh1: %s: Not a directory\n", dir);
	else if (status == EACCES)
		printf("yosh1: %s: Permission denied\n", dir);
	else if (status == EISDIR)
		printf("yosh1: %s: Is a directory\n", dir);
	else if (status == ENAMETOOLONG)
		printf("yosh1: %s: File name too long\n", dir);
	else if (status == ELOOP)
	    printf("yosh1: %s: Too many levels of symbolic links\n", dir);
	else if (status == EIO)
		printf("yosh1: %s: Input/output error\n", dir);
	else if (status == ENOMEM)
		printf("yosh1: %s: Cannot allocate memory\n", dir);
	else if (status == EFAULT)
		printf("yosh1: %s: Bad address\n", dir);
	else
		printf("yosh1: %s: %d\n", dir, errno);
}

static void	safe_open(int *fd, int *red, const char *__file, int __oflag)
{
	(*fd) = open(__file, __oflag, 0666);
	if ((*fd) == -1)
	{
		print_open_error(errno, __file);
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
