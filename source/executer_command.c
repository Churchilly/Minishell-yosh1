/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 18:03:08 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "builtins.h"

// assuming node is type of NODE_COMMAND
// return -1 on error
// every fucking command must update _= (enviroment variable). 
char	*search_executable_path(char *file_path);
char	**env_mirror();
void	update_last_execute(char *path);

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	execute_command(t_astnode *node)
{
	char	*path;
	int		argc;

	argc = count_args(node->args);
	if (is_builtin(node->args[0]))
	{
		execute_builtin(node->args[0], argc, node->args);
		return ;
	}
	path = search_executable_path(node->args[0]);
	if (!path)
	{
		printf("%s: command not found\n", *(node->args));
		exit(127);
	}
	if (execve(path, node->args, env_mirror()) == -1)
	{
		printf("execve() failed: %d.\n", errno);
		exit(1);
	}
	update_last_execute(path);
	exit(0);
}
