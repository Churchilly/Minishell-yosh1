/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:06:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 14:40:14 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static void	print_open_error(int status, const char *dir)
{
	if (status == ENOENT)
		printf("yosh1: %s: No such file or directory\n", dir);
	else if (status == ENOTDIR)
		printf("yosh1: %s: Not a directory\n", dir);
	else if (status == EACCES)
		printf("yosh1: %s: Permission denied\n", dir);
	else if (status == EISDIR)
		printf("yosh1: %s: Is a directory\n", dir);
	else if (status == ENAMETOOLONG)
		printf("yosh1: %s: File name too long\n", dir);
	else if (status == ELOOP)
		printf("yosh1: %s: Too many levels of symbolic links\n", dir);
	else if (status == EIO)
		printf("yosh1: %s: Input/output error\n", dir);
	else if (status == ENOMEM)
		printf("yosh1: %s: Cannot allocate memory\n", dir);
	else if (status == EFAULT)
		printf("yosh1: %s: Bad address\n", dir);
	else
		printf("yosh1: %s: %d\n", dir, errno);
}

void	safe_open(int *fd, int *red, const char *__file, int __oflag)
{
	(*fd) = open(__file, __oflag, 0666);
	if ((*fd) == -1)
	{
		print_open_error(errno, __file);
		exit(1);
	}
	if ((*red) == STDIN_FILENO || (*red) == STDOUT_FILENO)
		(*red) = (*fd);
}
