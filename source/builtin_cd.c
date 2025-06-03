/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:57:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "environment.h"
#include "garbage_collector.h"
#include "str.h"
#include <stdio.h>
#include <unistd.h>

static void	print_cd_error(int status, char *dir)
{
	if (status == ENOENT)
		printf("yosh1: cd: %s: No such file or directory\n", dir);
	else if (status == ENOTDIR)
		printf("yosh1: cd: %s: Not a directory\n", dir);
	else if (status == EACCES)
		printf("yosh1: cd: %s: Permission denied\n", dir);
	else if (status == EISDIR)
		printf("yosh1: cd: %s: Is a directory\n", dir);
	else if (status == ENAMETOOLONG)
		printf("yosh1: cd: %s: File name too long\n", dir);
	else if (status == ELOOP)
		printf("yosh1: cd: %s: Too many levels of symbolic links\n", dir);
	else if (status == EIO)
		printf("yosh1: cd: %s: Input/output error\n", dir);
	else if (status == ENOMEM)
		printf("yosh1: cd: %s: Cannot allocate memory\n", dir);
	else if (status == EFAULT)
		printf("yosh1: cd: %s: Bad address\n", dir);
	else
		printf("yosh: cd: %s: %d\n", dir, errno);
}

static int	update_pwd(void)
{
	t_node	*tmp;
	char	cwd[8000];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("getcwd() failed: %d\n", errno);
		return (1);
	}
	tmp = find_variable("PWD");
	if (tmp)
		revalue_variable("PWD", cwd);
	else
		add_variable("PWD", cwd);
	return (0);
}

static void	update_oldpwd(char *old_dir)
{
	t_node	*tmp;

	tmp = find_variable("OLDPWD");
	if (tmp)
		revalue_variable("OLDPWD", old_dir);
	else
		add_variable("OLDPWD", old_dir);
}

int	builtin_cd(int argc, char **args)
{
	char	*home_dir;
	char	*target_dir;
	char	*old_dir;
	int		status;

	home_dir = get_variable("HOME");
	if (!home_dir || !(*home_dir))
	{
		printf("yosh1: cd: HOME not set\n");
		return (1);
	}
	else if (argc == 1)
		target_dir = home_dir;
	else if (argc == 2)
		target_dir = args[1];
	else if (argc != 1)
		return (printf("yosh1: cd: too many arguments\n"));
	old_dir = ft_strdup(get_cwd(), SECTION_LA);
	status = chdir(target_dir);
	if (status == -1)
		return (print_cd_error(errno, target_dir), 1);
	if (update_pwd())
		return (1);
	update_oldpwd(old_dir);
	return (0);
}
