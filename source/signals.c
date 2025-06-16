/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:12:15 by yusudemi          #+#    #+#             */
/*   Updated: 2025/06/16 15:13:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <readline/readline.h>
#include "environment.h"

void	*pointer_storage(int type, void *ptr);

static void	handle_sigint(int sig)
{
	t_environment	*env;

	(void)sig;
	env = pointer_storage(ENVIRONMENT, NULL);
	env->last_pipe = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	setup_parent_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}

void	handle_child_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

int	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_child_sigint;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	return (0);
}
