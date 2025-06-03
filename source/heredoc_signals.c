/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:22:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/05/28 16:00:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include "environment.h"

extern volatile int g_signal;

void	*pointer_storage(int type, void *ptr);

void	setup_heredoc_child_signals(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
}