/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:19:21 by obastug           #+#    #+#             */
/*   Updated: 2025/05/31 16:56:29 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "environment.h"

void *pointer_storage(int type, void *ptr);
int	is_env_char(char c);
void	update_last_pipe(int status);


char *ft_substr(char const *s, unsigned int start, size_t len,
				t_section section);

void	print_all_variables(void)
{
	t_node *head;
	t_environment *env;

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
void	builtin_export(char **args)
{
	int i;
	int status;
	char *equal_pos;
	// If no args, print all exported variables
	if (!args[1])
	{
		print_all_variables();
		return;
	}
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		status = add_export(args[i], equal_pos);
		if (status)
			printf("yosh1: export: `%s': not a valid identifier\n", args[i]);
		i++;
		update_last_pipe(status);
	}
}

void builtin_unset(char **args)
{
	int i;

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
	t_node *head;
	t_environment *env;

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
