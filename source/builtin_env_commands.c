/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/05/27 18:26:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "environment.h"

void	*pointer_storage(int type, void *ptr);

char	*ft_substr(char const *s, unsigned int start, size_t len,
	t_section section);

void	builtin_export(char **args)
{
	int		i;
	char	*equal_pos;
	char	*key;
	char	*value;

	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
		{
			key = ft_substr(args[i], 0, equal_pos - args[i], SECTION_ENV);
			value = ft_strdup(equal_pos + 1, SECTION_ENV);
			if (!find_variable(key))
				add_variable(key, value);
			else
				revalue_variable(key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

void	builtin_unset(char **args)
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
}

void	builtin_printenv(void)
{
	t_node	*head;
	t_environment	*env;

	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);

	head = env->top;
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return ;
}
