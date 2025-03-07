/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:08:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/04 23:46:02 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
char	*get_cwd(t_enviroment *env)
{
	t_node	*tmp;

	tmp = find_variable(env, "PWD");
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

char	*get_variable(t_enviroment *env, char *key)
{
	t_node	*tmp;
	
	if (ft_strcmp(key, "?"))
		return (ft_strdup("42"));
	tmp = find_variable(env, key);
	if (!tmp)
		return (ft_strdup(""));
	return (tmp->value);
}

int	setup_paths(t_enviroment *env)
{
	t_node	*tmp;
	char	cwd[8000];
	
	tmp = find_variable(env, "PWD");
	if (!getcwd(cwd, sizeof(cwd)))
		return (-1);
	if (tmp)
	{
		if (revalue_variable(env, "PWD", cwd))
			return (-1);
	}
	else
		if (add_variable(env, "PWD", cwd))
			return (-1);
	tmp = find_variable(env, "OLDPWD");
	if (tmp)
	{
		if (revalue_variable(env, "OLDPWD", NULL))
			return (-1);
	}
	else
		if (add_variable(env, "OLDPWD", NULL))
			return (-1);
	tmp = find_variable(env, "OLDPWD");
	return (0);
}

int	setup_enviroment(t_enviroment *env)
{
	extern char	**environ;
	char		*equal_sign;
	char		*key;
	char		*value;
	int			i;
	
	env->bottom = NULL;
	env->top = NULL;
	if (!environ)
		return (-1); // return ENV_ERROR -> int	clear_env
	i = -1;
	while (environ[++i])
	{
		equal_sign = ft_strchr(environ[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(environ[i], equal_sign - environ[i]);
			value = ft_strdup(equal_sign + 1);
			if (!key || !value || add_variable(env, key, value) == -1)
				return (clear_enviroment(env));
			free(key);
			free(value);
		}
	}
	return (0);
}
