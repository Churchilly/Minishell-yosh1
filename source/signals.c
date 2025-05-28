/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:12:15 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 14:31:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern volatile int g_signal;

#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <readline/readline.h>
#include "environment.h"
/*
   The termios structure
       Many of the functions described here have a termios_p argument that is a pointer to a
       termios structure.  This structure contains at least the following members:

           tcflag_t c_iflag;       input modes 
           tcflag_t c_oflag;       output modes 
           tcflag_t c_cflag;       control modes 
           tcflag_t c_lflag;       local modes 
           cc_t     c_cc[NCCS];    special characters 
*/
void	*pointer_storage(int type, void *ptr);

static void	handle_sigint(int sig)
{
	t_environment *env;

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
	
	rl_getc_function = rl_getc;
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
