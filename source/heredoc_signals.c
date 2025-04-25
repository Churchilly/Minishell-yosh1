/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:22:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/22 02:00:59 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern volatile int g_signal;

#include <signal.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include "enviroment.h"

void	*pointer_storage(int type, void *ptr);

static void	handle_sigint_child_heredoc(int sig)
{
	t_enviroment *env;

	g_signal = sig;
	env = pointer_storage(ENVIROMENT, NULL);
	env->last_pipe = 130;
	exit(0);
}
void	setup_heredoc_child_signals(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_sigint_child_heredoc;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
}