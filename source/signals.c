/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:12:15 by yusudemi          #+#    #+#             */
/*   Updated: 2025/03/08 06:41:35 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include "enviroment.h"

//when ctr-c -> last exit status = 130
void	handle_sigint(int sig)
{
	(void)sig;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigterm(int sig)
{
	(void)sig;
}

int	setup_signal_handlers(t_enviroment *env)
{
	struct sigaction	sa;
	sigemptyset(sa);
}