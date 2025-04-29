/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:43:36 by obastug           #+#    #+#             */
/*   Updated: 2025/04/29 20:20:39 by yusudemi         ###   ########.fr       */
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


int	create_redirection(t_astnode *node, int redirect_to, int redirect_from);

extern char **__environ;
// assuming node is type of NODE_COMMAND
// return -1 on error
int	execute_command_node(t_astnode *node)
{
	char	**env = __environ;
	char	*path;

	path = search_executable_path(node->args[0]);
	if (!path)
	{
		printf("%s: command not found\n", *(node->args));
		exit(1);
	}
	if (execve(path, node->args, env) == -1)
	{
		perror("execve");
		return (-1);
	}
	return (0);
}

void	execute_redirection(t_astnode *node, int red_to, int red_from, int fd)
{
	pid_t	pid;
	
	if (red_from == STDOUT_FILENO)
		red_from = fd;
	if (node->left && node->left->type == NODE_REDIRECT)
		create_redirection(node->left, red_to, red_from);
	else if (node->left && node->left->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(red_from, STDIN_FILENO);
			dup2(red_to, STDOUT_FILENO);
			close(red_from);
			close(red_to);
			execute_command_node(node->left);
			exit(0);
		}
		else
		{
			close(red_from);
			close(red_to);
			waitpid(pid, NULL, 0);
		}
	}
}

//-2 no node
//-1 no file
int	create_redirection(t_astnode *node, int redirect_to, int redirect_from)
{
	int		fd;

	if (!node)
		return (-2);
	if (node->redirect_type == TOKEN_GREAT)
	{
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		execute_redirection(node, redirect_to, redirect_from, fd);
	}
	if (node->redirect_type == TOKEN_DGREAT)
	{
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		execute_redirection(node, redirect_to, redirect_from, fd);
	}
	else if (node->redirect_type == TOKEN_LESS)
	{
		fd = open(node->file, O_RDONLY, 0666);
		execute_redirection(node, redirect_to, redirect_from, fd);
	}
	return (0);
}

void	execute_pipe(t_astnode *node)
{
	int pipedes[2]; // File descriptors for the pipe
	pid_t	pid;

	pipe(pipedes); // Create a pipe
	pid = fork(); // Fork the process
	if (pid == 0)
	{
		close(pipedes[0]); // Close the read end of the pipe
		dup2(pipedes[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
		if (node && node->left && node->left->type == NODE_PIPE)
			execute_pipe(node->left);
		else if (node && node->left && node->left->type == NODE_COMMAND)
			execute_command_node(node->left);
		close(pipedes[1]); // Close the write end after duplicating
		exit(0);
	}
	if (pid)
	{
		close(pipedes[1]); // Close the write end of the pipe
		dup2(pipedes[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
		execute_command_node(node->right);
		close(pipedes[0]); // Close the read end after duplicating
	}
}

// 3 -> systemcall error
// 2 -> execution error
// 1 -> no node
void	execute_valid_tree(t_astnode *node)
{
	pid_t	pid;

	if (node->type == NODE_PIPE)
	{
		pid = fork();
		if (pid == 0)
			execute_pipe(node);
		else
			waitpid(pid, NULL, 0);
	}
	else if (node->type == NODE_REDIRECT)
	{
		pid = fork();
		if (pid == 0)
			create_redirection(node, STDIN_FILENO, STDOUT_FILENO);
		else
			waitpid(pid, NULL, 0);
	}
	else if (node->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid == 0)
			execute_command_node(node);
		else
			waitpid(pid, NULL, 0);
	}
}

// returns 0 on success
// returns 1 on error
void	executer(t_astnode *root)
{
	execute_valid_tree(root);
}
