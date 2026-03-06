/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/06 14:04:19 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_file(t_redir *redirections)
{
	int	fd;

	if (redirections->type == TOKEN_REDIR_IN)
		fd = open(redirections->target, O_RDONLY);
	else if (redirections->type == TOKEN_REDIR_OUT)
		fd = open(redirections->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redirections->type == TOKEN_REDIR_APPEND)
		fd = open(redirections->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

static void	redirect_fd(int fd, t_token_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirections)
{
	int	fd;

	while (redirections)
	{
		if (redirections->type == TOKEN_HEREDOC)
		{
			if (redirections->fd != -1)
				redirect_fd(redirections->fd, redirections->type);
		}
		else
		{
			fd = open_file(redirections);
			if (fd == -1)
			{
				perror(redirections->target);
				exit(1);
			}
			redirect_fd(fd, redirections->type);
		}
		redirections = redirections->next;
	}
}
