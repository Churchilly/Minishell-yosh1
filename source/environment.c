/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:08:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/31 15:03:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>

extern volatile int	g_signal;

void	*pointer_storage(int type, void *ptr);

char	*get_cwd(void)
{
	t_node			*tmp;

	tmp = find_variable("PWD");
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

char	*get_variable(char *key)
{
	t_environment	*env;
	t_node			*tmp;

	if (!key)
		return (NULL);
	env = (t_environment *)pointer_storage(ENVIRONMENT, NULL);
	if (ft_strcmp(key, "?"))
		return (ft_itoa(env->last_pipe, SECTION_LA));
	tmp = find_variable(key);
	if (!tmp)
		return (ft_strdup("", SECTION_LA));
	return (ft_strdup(tmp->value, SECTION_LA));
}

void	update_execute(char *path)
{
	t_node	*last_exec;

	last_exec = find_variable("_");
	if (!last_exec)
		add_variable("_", path);
	else
		revalue_variable("_", path);
	return ;
}

void	update_last_pipe(int status)
{
	t_environment	*env;

	env = pointer_storage(ENVIRONMENT, NULL);
	env->last_pipe = status;
}

int	is_env_char(char c)
{
	return ((c <= '9' && c >= '0')
		|| (c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A')
		|| (c == '_'));
}
