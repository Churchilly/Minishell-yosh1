/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:12:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:20:56 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "str.h"
#include "minishell.h"

void	*env_calloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		printf("malloc() failed: %d\n", errno);
		exit(1);
	}
	ft_bzero(new, size);
	return (new);
}

char	*create_env_value(char *str)
{
	int		len;
	int		i;
	char	*ret;

	if (!str)
	{
		return (env_calloc(sizeof(char) * 1));
	}
	len = 0;
	while (str[len])
		len++;
	ret = env_calloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	return (ret);
}

void	clear_environment(void)
{
	t_node			*tmp;
	t_environment	*env;

	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	if (!env)
		return ;
	while (env->top)
	{
		tmp = env->top;
		env->top = env->top->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
