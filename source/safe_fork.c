/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:44:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/03 15:15:44 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"

int	safe_fork(void)
{
	t_garbage_collector	*gc;
	pid_t				pid;
	
	pid = fork();
	if (pid == -1)
	{
		printf("fork() failed: %d.\n", errno);
		exit(1);
	}
	gc = pointer_storage(COLLECTOR, NULL);
	if (pid == 0)
		gc->in_fork = 1;
	return (pid);
}