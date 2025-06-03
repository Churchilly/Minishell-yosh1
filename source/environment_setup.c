/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:23:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:37 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"

static int	check_oldpwd_accessible(char *oldpwd)
{
	if (access(oldpwd, F_OK))
		return (1);
	return (0);
}

static void	setup_paths(void)
{
	t_node	*tmp;
	char	cwd[8000];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("getcwd() failed: %d\n", errno);
		exit(1);
	}
	tmp = find_variable("PWD");
	if (tmp)
		revalue_variable("PWD", cwd);
	else
	{
		add_variable("PWD", cwd);
	}
	tmp = find_variable("OLDPWD");
	if (tmp && !check_oldpwd_accessible(tmp->value))
	{
		tmp = find_variable("HOME");
		revalue_variable("OLDPWD", tmp->value);
	}
}

static char	*increase_charp(char *str)
{
	return (ft_itoa(ft_atoi(str) + 1, SECTION_LA));
}

static void	setup_shlvl(void)
{
	t_node	*tmp;

	tmp = find_variable("SHLVL");
	if (tmp)
		revalue_variable("SHLVL", increase_charp(tmp->value));
	else
		add_variable("SHLVL", "0");
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
			key = ft_strndup(environ[i], equal_sign - environ[i], SECTION_LA);
			value = equal_sign + 1;
			add_variable(key, value);
		}
	}
	setup_paths();
	setup_shlvl();
}
