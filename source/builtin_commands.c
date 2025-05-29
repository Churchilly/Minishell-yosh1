/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/05/27 18:23:41 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>
#include "environment.h"
#include "builtins.h"
#include "environment.h"

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[i], "-n"))
		i++;
	while (args[i])
	{
		if (i != 0)
			ft_putchar(' ');
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (ft_strcmp(args[i], "-n"))
		putchar('\n');
	return (0);
}

// if no arguments were given go to home directory
// if 1 argument were given go to that directory
int	builtin_cd(int argc, char **args)
{
	char	*home_dir;

	
	home_dir = get_variable("HOME"); //getenv("HOME")
	if (argc == 1)
	{
		chdir(home_dir);
	}
	else if (argc == 2)
		chdir(args[1]);
	else
		return (1);
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = get_cwd();
	printf("%s\n", buf);
	return (0);
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "printenv") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char *command, int argc, char **args)
{
	if (ft_strcmp(command, "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(command, "cd") == 0)
	{
		builtin_cd(argc, args);
		return (0);
	}
	if (ft_strcmp(command, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(command, "export") == 0)
	{
		builtin_export(args);
		return (0);
	}
	if (ft_strcmp(command, "unset") == 0)
	{
		builtin_unset(args);
		return (0);
	}
	if (ft_strcmp(command, "printenv") == 0)
	{
		builtin_printenv();
		return (0);
	}
	return (1);
}