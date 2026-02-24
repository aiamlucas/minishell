/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/24 17:53:30 by lbueno-m         ###   ########.fr       */
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

static void	init_child_data(t_child_data *child_data, int **pipes,
							int count, t_data parent_data)
{
	child_data->pipes = pipes;
	child_data->total = count;
	child_data->envp = parent_data.envp;
	child_data->internal_env = parent_data.internal_env;
}

static pid_t	fork_one_child(t_child_data *data, t_command *cmd, int index)
{
	data->cmd = cmd;
	data->cmd_index = index;
	return (fork_child(data));
}

int	execute_pipeline(t_command *cmds, t_data parent_data)
{
	int				count;
	int				**pipes;
	pid_t			last_pid;
	int				i;
	t_child_data	child_data;
	int				exit_code;

	count = count_pipeline_commands(cmds);
	pipes = create_pipes(count - 1);
	if (!pipes)
		return (1);
	init_child_data(&child_data, pipes, count, parent_data);
	i = 0;
	while (cmds && i < count)
	{
		last_pid = fork_one_child(&child_data, cmds, i);
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
