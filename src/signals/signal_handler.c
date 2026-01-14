/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:25:08 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/14 15:35:01 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_signal_received = 0;
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	reset_signals(void)
{
	struct sigaction	sa;

	g_signal_received = 0;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
