/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 17:31:07 by lbueno-m         ###   ########.fr       */
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
							int count, char **envp)
{
	data->pipes = pipes;
	data->total = count;
	data->envp = envp;
}

static pid_t	fork_one_child(t_child_data *data, t_command *cmd, int i)
{
	data->cmd = cmd;
	data->i = i;
	return (fork_child(data));
}

int	execute_pipeline(t_command *cmds, char **envp)
{
	int				count;
	int				**pipes;
	pid_t			last_pid;
	int				i;
	t_child_data	data;

	count = count_pipeline_commands(cmds);
	pipes = create_pipes(count - 1);
	if (!pipes)
		return (1);
	init_child_data(&data, pipes, count, envp);
	i = -1;
	while (cmds && ++i < count)
	{
		last_pid = fork_one_child(&data, cmds, i);
		if (last_pid == -1)
			return (cleanup_on_error(pipes, count));
		cmds = cmds->next;
	}
	return (wait_all(last_pid, pipes, count));
}
