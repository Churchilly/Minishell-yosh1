/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:29:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/27 04:26:08 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <unistd.h>

void	*pointer_storage(int type, void *ptr);

t_node	*find_variable(char *key)
{
	t_enviroment	*env;
	t_node			*ret;

	env = (t_enviroment *)pointer_storage(ENVIROMENT, NULL);
	ret = env->top;
	while (ret)
	{
		if (ft_strcmp(ret->key, key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

void	delete_variable(char *key)
{
	t_enviroment	*env;
	t_node			*prev;
	t_node			*to_delete;

	env = (t_enviroment *)pointer_storage(ENVIROMENT, NULL);
	to_delete = env->top;
	prev = NULL;
	while (to_delete)
	{
		if (ft_strcmp(to_delete->key, key))
		{
			if (prev)
				prev->next = to_delete->next;
			else
				env->top = to_delete->next;
			if (to_delete == env->bottom)
				env->bottom = prev;
			free(to_delete->key);
			free(to_delete->value);
			free(to_delete);
			return ;
		}
		prev = to_delete;
		to_delete = to_delete->next;
	}
}

int	revalue_variable(char *key, char *value)
{
	t_node	*node;
	char	*tmp;

	node = find_variable(key);
	if (!node)
		return (-1);
	tmp = node->value;
	node->value = ft_strdup(value, SECTION_ENV);
	free(tmp);
	if (!node->value)
		return (-1);
	return (0);
}

void	add_variable(char *key, char *value)
{
	t_enviroment	*env;
	t_node			*new;

	env = (t_enviroment *)pointer_storage(ENVIROMENT, NULL);
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		exit(1); // malloc err
	new->key = ft_strdup(key, SECTION_ENV);
	new->value = ft_strdup(value, SECTION_ENV);
	new->next = NULL;
	if (!env->top)
	{
		env->top = new;
		env->bottom = new;
		return ;
	}
	env->bottom->next = new;
	env->bottom = new;
	return ;
}

void	clear_enviroment(void)
{
	t_node			*tmp;
	t_enviroment	*env;
	
	env = (t_enviroment *)pointer_storage(ENVIROMENT, NULL);
	if (!env)
		return ;
	while (env->top)
	{
		tmp = env->top;
		env->top = env->top->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
