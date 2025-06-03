/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 16:39:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>
#include "environment.h"
#include "builtins.h"
#include <errno.h>

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo"))
		return (1);
	if (ft_strcmp(command, "cd"))
		return (1);
	if (ft_strcmp(command, "pwd"))
		return (1);
	if (ft_strcmp(command, "export"))
		return (1);
	if (ft_strcmp(command, "unset"))
		return (1);
	if (ft_strcmp(command, "env"))
		return (1);
	if (ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char *command, int argc, char **args)
{
	int	status;

	status = 1;
	if (ft_strcmp(command, "echo"))
		status = builtin_echo(args);
	else if (ft_strcmp(command, "cd"))
		status = builtin_cd(argc, args);
	else if (ft_strcmp(command, "pwd"))
		status = builtin_pwd();
	else if (ft_strcmp(command, "export"))
		status = builtin_export(args);
	else if (ft_strcmp(command, "unset"))
		status = builtin_unset(args);
	else if (ft_strcmp(command, "env"))
		status = builtin_printenv(args);
	else if (ft_strcmp(command, "exit"))
		builtin_exit(args);
	return (status);
}
