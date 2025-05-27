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
#include <stdlib.h>
#include <stdio.h>
#include "environment.h"

int	echo(char **args)
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
int	cd(int argc, char **args)
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

int	pwd(void)
{
	char	*buf;

	buf = get_cwd();
	printf("%s\n", buf);
	return (0);
}
