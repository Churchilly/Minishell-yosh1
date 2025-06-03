/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 16:55:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"
#include <stdlib.h>

static int	is_arg_numeric(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **args)
{
	t_environment	*env;

	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	if (!args[1])
		exit(env->last_pipe);
	if (!is_arg_numeric(args[1]))
	{
		printf("exit\nyosh1: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		printf("exit\nyosh1: exit: too many arguments\n");
		return (update_last_pipe(1));
	}
	printf("exit\n");
	exit(ft_atoi(args[1]) & 255);
}
