/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:02 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "builtins.h"
#include "environment.h"
#include "executer.h"
#include "minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

// before run command check if it already a path
// like /cat is different from cat
// is a directory ?? 
void	execute_command(t_astnode *node)
{
	char	*path;
	int		argc;

	argc = count_args(node->args);
	if (is_builtin(node->args[0]))
	{
		update_execute(node->args[argc - 1]);
		update_last_pipe(execute_builtin(node->args[0], argc, node->args));
		return ;
	}
	path = search_executable_path(node->args[0]);
	if (!path)
	{
		printf("%s: command not found\n", *(node->args));
		exit(127);
	}
	update_execute(path);
	if (execve(path, node->args, env_mirror()) == -1)
	{
		printf("execve() failed: %d.\n", errno);
		exit(1);
	}
	exit(0);
}
