/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/14 17:05:08 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cleanup_on_error(int **pipes, int count)
{
	close_pipes(pipes, count - 1);
	free_pipes(pipes, count - 1);
	return (1);
}

static int	wait_all(pid_t last_pid, int **pipes, int count)
{
	int	status;

	close_pipes(pipes, count - 1);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	free_pipes(pipes, count - 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	init_child_data(t_child_data *data, int **pipes,
							int count, char **envp, int heredoc_fd)
{
	data->pipes = pipes;
	data->total = count;
	data->envp = envp;
	data->heredoc_fd = heredoc_fd;
}

static pid_t	fork_one_child(t_child_data *data, t_command *cmd, int index, int heredoc_fd)
{
	data->cmd = cmd;
	data->cmd_index = index;
	data->heredoc_fd = heredoc_fd;
	return (fork_child(data));
}

int	execute_pipeline(t_command *cmds, char **envp, int heredoc_fd)
{
	int				count;
	int				**pipes;
	pid_t			last_pid;
	int				i;
	t_child_data	data;
	int				exit_code;

	count = count_pipeline_commands(cmds);
	pipes = create_pipes(count - 1);
	if (!pipes)
		return (1);
	init_child_data(&data, pipes, count, envp, heredoc_fd);
	i = 0;
	while (cmds && i < count)
	{
		last_pid = fork_one_child(&data, cmds, i, heredoc_fd);
		if (last_pid == -1)
			return (cleanup_on_error(pipes, count));
		cmds = cmds->next;
		i++;
	}
	exit_code = wait_all(last_pid, pipes, count);
	if (check_signal())
		return (get_signal_exit_code());
	return (exit_code);
}
