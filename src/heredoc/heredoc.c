/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:05 by ssin              #+#    #+#             */
/*   Updated: 2026/03/10 18:58:15 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_child(t_data *data, int *fd)
{
	reset_signals();
	read_heredoc(data, fd);
}

static int	wait_child(pid_t pid, int status, t_data *data,
					t_redir *saved_redir)
{
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, data->t_settings);
	data->commands->redirections = saved_redir;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static int	create_child(t_data *data, t_redir *redir, int *fd)
{
	int		status;
	pid_t	pid;
	t_redir	*saved_redir;
	int		result; // added

	if (!set_fd(fd))
		return (-1);
	saved_redir = data->commands->redirections;
	data->commands->redirections = redir;
	status = 0;
	pid = fork();
	if (pid == ERROR)
	{
		ft_printf("heredoc error pid\n");
		data->commands->redirections = saved_redir;
		return (-1);
	}
	if (pid == CHILD)
		execute_child(data, fd);
	close(fd[1]);
	update_sigint(handle_sigint_child);
	result = wait_child(pid, status, data, saved_redir);
	if (result != 0 || g_signal_received)
		close(fd[0]);
	update_sigint(handle_sigint_parent);
	return (result);
}

int	process_all_heredocs(t_data *data)
{
	t_command	*cmd;
	t_redir		*redir;
	int			fd[2];
	int			exit_code;

	cmd = data->commands;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				if (redir->fd != -1)
					close(redir->fd);
				exit_code = create_child(data, redir, fd);
				if (handle_heredoc_error(exit_code, fd))
					return (exit_code);
				redir->fd = fd[0];
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
