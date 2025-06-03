/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 17:47:17 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"
#include <stdlib.h>
#include <limits.h>

static int	is_arg_numeric(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i] && (arg[i] >= '0' && arg[i] <= '9'))
		i++;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	get_sign(int *i, char *arg)
{
	int	sign;

	sign = 1;
	if (arg[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (arg[*i] == '+')
		(*i)++;
	return (sign);
}

static int	check_overflow(char *arg)
{
	int			i;
	long long	number;
	int			sign;

	if (!arg)
		return (0);
	i = 0;
	number = 0;
	while (ft_isspace(arg[i]))
		i++;
	sign = get_sign(&i, arg);
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		if (number > (LONG_MAX - (arg[i] - '0')) / 10)
			return (0);
		number = number * 10 + (arg[i] - '0');
		i++;
	}
	if (sign == -1
		&& (unsigned long long)number > (unsigned long long)LONG_MAX + 1)
		return (0);
	else if (number > LONG_MAX)
		return (0);
	return (1);
}

void	builtin_exit(char **args)
{
	t_environment	*env;

	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	if (!args[1])
		exit(env->last_pipe);
	if (!is_arg_numeric(args[1]) || !check_overflow(args[1]))
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
