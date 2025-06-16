/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:01:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/16 17:11:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

void	print_all_variables(void)
{
	t_node			*head;
	t_environment	*env;

	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	head = env->top;
	while (head)
	{
		if (head->value)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

int	is_valid_identifier(char *id)
{
	int	i;

	if (!id || !(*id))
		return (0);
	if (!is_env_char(*id) || (*id <= '9' && *id >= '0'))
		return (0);
	i = 1;
	while (id[i] && id[i] != '=')
	{
		if (!is_env_char(id[i]))
			return (0);
		i++;
	}
	return (1);
}

int	add_export(char	*args, char *equal_pos)
{
	char	*key;
	char	*value;

	if (equal_pos)
	{
		key = ft_substr(args, 0, equal_pos - args, SECTION_LA);
		if (!is_valid_identifier(key))
			return (1);
		value = ft_strdup(equal_pos + 1, SECTION_LA);
		if (!find_variable(key))
			add_variable(key, value);
		else
			revalue_variable(key, value);
	}
	else
	{
		if (!is_valid_identifier(args))
			return (1);
		if (!find_variable(args))
			add_variable(ft_strdup(args, SECTION_LA), NULL);
	}
	return (0);
}

int	builtin_export(char **args)
{
	int		i;
	int		status;
	char	*equal_pos;

	if (!args[1])
	{
		print_all_variables();
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		status = add_export(args[i], equal_pos);
		if (status)
			return (printf("yosh1: export: `%s': not a valid identifier\n",
					args[i]), 1);
		i++;
	}
	return (0);
}
