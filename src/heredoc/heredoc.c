/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:05 by ssin              #+#    #+#             */
/*   Updated: 2026/02/11 11:12:40 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_heredoc(t_redir redirections)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_printf("error pipe\n");
	pid = fork();
	if (pid == -1)
		ft_printf("error pid\n");
	if (pid == 0)
		read_heredoc(redirections, fd);
	wait(pid);
}

int	handle_heredoc(t_redir redirections)
{
	create_heredoc(redirections);
	return (0);
}
