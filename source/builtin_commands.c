/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/05/29 17:59:58 by yusudemi         ###   ########.fr       */
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
	int j;

	i = 1;
	j = 0;
	if (ft_strcmp(args[i], "-n"))
		i++;
	while (args[i])
	{
		if (j)
			ft_putchar(' ');
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		j = 1;
	}
	if (ft_strcmp(args[1], "-n") == 0)
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
	return (0);
}

int	execute_builtin(char *command, int argc, char **args)
{
	if (ft_strcmp(command, "echo"))
		return (builtin_echo(args));
	if (ft_strcmp(command, "cd"))
	{
		builtin_cd(argc, args);
		return (0);
	}
	if (ft_strcmp(command, "pwd"))
		return (builtin_pwd());
	if (ft_strcmp(command, "export"))
	{
		builtin_export(args);
		return (0);
	}
	if (ft_strcmp(command, "unset"))
	{
		builtin_unset(args);
		return (0);
	}
	if (ft_strcmp(command, "env"))
	{
		builtin_printenv();
		return (0);
	}
	return (1);
}