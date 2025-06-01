/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:12:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/01 18:19:45 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void	*pointer_storage(int type, void *ptr);
void	ft_bzero(void *addr, int size);

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
