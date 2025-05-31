/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path_finder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:17:16 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/30 20:51:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "str.h"
#include "parser.h"

int	is_already_path(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

static int	is_file_executable(const char *file_path)
{
	struct stat	sb;

	if (!ft_strchr(file_path, '/'))
		return (0);
	if (stat(file_path, &sb) == 0 && S_ISREG(sb.st_mode)
		&& (sb.st_mode & S_IXUSR))
		return (1);
	return (0);
}

static char	*is_file_executable_in_path(char **path_list, char *file_path)
{
	int		i;
	char	*final_path;

	i = 0;
	file_path = ft_strjoin("/", file_path, SECTION_LA);
	while (path_list[i])
	{
		final_path = ft_strjoin(path_list[i], file_path, SECTION_LA);
		if (is_file_executable(final_path))
			return (final_path);
		i++;
	}
	return (NULL);
}

char	*search_executable_path(char *file_path)
{
	char	*env_path;
	char	**path_list;
	char	*final_path;

	if (is_file_executable(file_path))
		return (file_path);
	if (is_already_path(file_path))
	{
		printf("yosh1: %s: No such file or directory\n", file_path);
		exit(127);
	}
	env_path = get_variable("PATH");
	path_list = ft_split(env_path, ':', SECTION_LA);
	final_path = is_file_executable_in_path(path_list, file_path);
	if (!final_path)
		return (NULL);
	return (final_path);
}
