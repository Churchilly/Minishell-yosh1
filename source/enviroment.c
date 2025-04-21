/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:08:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 21:32:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>

extern volatile int g_signal;

void	*pointer_storage(int type, void *ptr);

char	*get_cwd()
{
	t_node			*tmp;

	tmp = find_variable("PWD");
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

char	*get_variable(char *key)
{
	t_enviroment	*env;
	t_node			*tmp;

	if (!key)
		return (NULL);
	env = (t_enviroment *)pointer_storage(ENVIROMENT, NULL);
	if (ft_strcmp(key, "?"))
		return (ft_itoa(env->last_pipe, SECTION_ENV));
	tmp = find_variable(key);
	if (!tmp)
		return (ft_strdup("", SECTION_ENV));
	return (ft_strdup(tmp->value, SECTION_ENV));
}

