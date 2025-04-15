/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:22:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/15 19:22:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern volatile int g_signal;

#include <signal.h>
#include <stddef.h>
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>

static void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
}

int	setup_heredoc_signals(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	return (0);
}

static void	handle_sigint_child_heredoc(int sig)
{
	g_signal = sig;
	close(0);
}
int	setup_heredoc_child_signals(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_sigint_child_heredoc;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	return (0);
}