/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/05/31 18:15:26 by yusudemi         ###   ########.fr       */
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
	int	newline;

	i = 1;
	j = 0;
	newline = 1;
	if (args[i] && ft_strcmp(args[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (j)
			ft_putchar(' ');
		if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
			return (1);
		i++;
		j = 1;
	}
	if (newline)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (1);
	return (0);
}	


int	builtin_cd(int argc, char **args) // fuck this cd fuck hands of who writes this cd fuck everything
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
	int status;

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
	return (status);
}