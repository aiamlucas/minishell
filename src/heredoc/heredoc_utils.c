/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:47:02 by ssin              #+#    #+#             */
/*   Updated: 2026/03/19 11:56:26 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_fd(int *fd)
{
	fd[0] = 0;
	fd[1] = 0;
	if (pipe(fd) == -1)
	{
		printf("heredoc error pipe\n");
		return (0);
	}
	return (1);
}

int	handle_heredoc_error(int exit_code)
{
	if (exit_code != 0 || g_signal_received)
		return (1);
	return (0);
}
