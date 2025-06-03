/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_unset_pwd_exit.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 16:40:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "environment.h"
#include "minishell.h"

int	builtin_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (find_variable(args[i]))
		{
			if (ft_strcmp(args[i], "SHLVL"))
				revalue_variable("SHLLVL", "0");
			else
				delete_variable(args[i]);
		}
		i++;
	}
	return (0);
}

int	builtin_printenv(char **args)
{
	t_node			*head;
	t_environment	*env;

	if (args[1])
		return (printf("yosh1: env: to many arguments\n"), 1);
	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	head = env->top;
	while (head)
	{
		if (!(head->value))
		{
			head = head->next;
			continue ;
		}
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = get_cwd();
	printf("%s\n", buf);
	return (0);
}


