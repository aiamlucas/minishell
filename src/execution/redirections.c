/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 18:06:14 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_file(t_redir *redirections)
{
	int	fd;

	if (redirections->type == TOKEN_REDIR_IN)
		fd = open(redirections->file, O_RDONLY);
	else if (redirections->type == TOKEN_REDIR_OUT)
		fd = open(redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redirections->type == TOKEN_REDIR_APPEND)
		fd = open(redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

static void	redirect_fd(int fd, t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
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
		fd = open_file(redirections);
		if (fd == -1 && redirections->type != TOKEN_HEREDOC)
		{
			perror(redirections->file);
			exit(1);
		}
		if (fd != -1)
			redirect_fd(fd, redirections->type);
		redirections = redirections->next;
	}
}
