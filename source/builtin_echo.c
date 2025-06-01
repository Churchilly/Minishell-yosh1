/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:00:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/31 19:00:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"

int	builtin_echo(char **args)
{
	int	i;
	int	j;
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
