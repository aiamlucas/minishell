/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:25:08 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/23 16:33:50 by lbueno-m         ###   ########.fr       */
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
	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell:sigaction SIGINT failed");
		exit(1);
	}
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("minishell: sigaction SIGQUIT failed");
		exit(1);
	}
}

void	reset_signals(void)
{
	struct sigaction	sa;

	g_signal_received = 0;
	ft_memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
