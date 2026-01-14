/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:39:57 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/14 17:07:58 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_signal(void)
{
	return (g_signal_received != 0);
}

void	reset_signal(void)
{
	g_signal_received = 0;
}
 

int		get_signal_exit_code(void)
{
	int code;
	if (g_signal_received == 0)
		return (0);
	code = 128 + g_signal_received;
	g_signal_received = 0;
	return (code);
}

bool	handle_signal_interrupt(void)
{
	if (!g_signal_received)
		return (false);
	g_signal_received = 0;
	return (true);
}
