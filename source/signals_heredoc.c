/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:22:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/04/13 20:30:43 by yusudemi         ###   ########.fr       */
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
	
	rl_getc_function = getc;
	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	return (0);
}