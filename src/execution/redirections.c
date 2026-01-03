/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/26 15:08:04 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	apply_redirections(t_redir *redirections)
{
	int	fd;

	while (redirections)
	{
		if (redirections->type == TOKEN_REDIR_IN)
			fd = open(redirections->file, O_RDONLY);
		else if (redirections->type == TOKEN_REDIR_OUT)
				fd = open(redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirections->type == TOKEN_REDIR_APPEND)
				fd = open(redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
		{
			redirections = redirections->next;
			continue ;
		}
		if (fd == -1)
		{
			perror(redirections->file);
			exit(1);
		}
		if (redirections->type == TOKEN_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirections = redirections->next;
	}
}
