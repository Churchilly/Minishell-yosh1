/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:00:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 18:29:35 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include <stdio.h>

// for -n -nnnn -nnnnnnnnn returns 1 else 0
int	is_ignore_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	print_args(char **args)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (args[i])
	{
		if (j)
			ft_putchar(' ');
		if (printf("%s", args[i]) == -1)
			return (1);
		i++;
		j = 1;
	}
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i])
	{
		if (is_ignore_newline(args[i]))
			newline = 0;
		else
			break ;
		i++;
	}
	if (print_args(args + i) == 1)
		return (1);
	if (newline)
		if (printf("\n") == -1)
			return (1);
	return (0);
}
