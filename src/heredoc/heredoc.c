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

	if (!set_fd(fd))
		return (-1);
	status = 0;
	pid = fork();
	if (pid == -1)
	{
		ft_printf("heredoc error pid\n");
		return (-1);
	}
	if (pid == 0)
	{
		// reset signals?
		read_heredoc(data->commands->redirections, fd, data->t_settings);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		tcsetattr(STDIN_FILENO, TCSANOW, data->t_settings);
	}
	// review exit codes
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	handle_heredoc(t_data *data, int *fd)
{
	int	exit_code;
	// Add tests
	if (!data->commands || !data->commands->redirections)
		return (0);
	if (data->commands->redirections->type != TOKEN_HEREDOC)
		return (0);
	if (!data->commands->redirections->next)
		return (create_heredoc(data, fd));
	else
	{
		while (data->commands->redirections)
		{
			exit_code = create_heredoc(data, fd);
			data->commands->redirections = data->commands->redirections->next;
		}
	}
	return (exit_code);
}
