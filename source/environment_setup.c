/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:23:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/27 17:51:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>

void	*pointer_storage(int type, void *ptr);

static void	setup_paths(void)
{
	t_node	*tmp;
	char	cwd[8000];
	
	tmp = find_variable("PWD");
	if (!getcwd(cwd, sizeof(cwd)))
		exit(1);
	if (tmp)
		revalue_variable("PWD", cwd);
	else
		add_variable("PWD", cwd);
	tmp = find_variable("OLDPWD");
	if (tmp)
		revalue_variable("OLDPWD", cwd);
	else
		add_variable("OLDPWD", cwd);
	tmp = find_variable("OLDPWD");
}

static void	setup_shlvl(void)
{
	t_node	*tmp;
	
	tmp = find_variable("SHLVL");
	if (tmp)
		revalue_variable("SHLVL", tmp->value + 1);
	else
		add_variable("SHLVL", 0);
}

void	setup_environment(void)
{
	extern char	**environ;
	char		*equal_sign;
	char		*key;
	char		*value;
	int			i;

	if (!environ)
		exit(1);
	i = -1;
	while (environ[++i])
	{
		equal_sign = ft_strchr(environ[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(environ[i], equal_sign - environ[i], SECTION_ENV);
			value = ft_strdup(equal_sign + 1, SECTION_ENV);
			add_variable(key, value);
		}
	}
	setup_paths();
	setup_shlvl();
}
