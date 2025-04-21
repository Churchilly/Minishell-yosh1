/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:23:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/21 21:32:20 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "str.h"
#include <unistd.h>
#include <stdlib.h>

void	*pointer_storage(int type, void *ptr);

void	setup_paths(void)
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
		revalue_variable("OLDPWD", NULL);
	else
		add_variable("OLDPWD", NULL);
	tmp = find_variable("OLDPWD");
}

void	setup_enviroment(void)
{
	extern char	**environ;
	char		*equal_sign;
	char		*key;
	char		*value;
	int			i;
	
	if (!environ)
		exit(1); // return ENV_ERROR -> int	clear_env
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
}
