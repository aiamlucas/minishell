/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:05 by ssin              #+#    #+#             */
/*   Updated: 2026/02/17 08:40:13 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_heredoc(t_data *data, int *fd)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		ft_printf("heredoc error pid\n");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		read_heredoc(data->commands->redirections, fd, data->t_settings);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		//close(fd[0]);
	}
	// review exit codes
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	handle_heredoc(t_data *data, int *fd)
{
	// Add tests
	if (!data->commands || !data->commands->redirections)
		return (0);
	if (data->commands->redirections->type != TOKEN_HEREDOC)
		return (0);
	if (!data->commands->redirections->next)
		create_heredoc(data, fd);
	else
	{
		while (data->commands->redirections)
		{
			create_heredoc(data, fd);
			data->commands->redirections = data->commands->redirections->next;
		}
	}
	return (0);
}
