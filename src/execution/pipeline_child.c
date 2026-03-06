/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:27:12 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/24 17:57:50 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_pipes(int **pipes, int cmd_index, int total)
{
	if (cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < total - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
}

void	child_process(t_child_data *data)
{
	reset_signals();
	setup_pipes(data->pipes, data->cmd_index, data->total);
	close_pipes(data->pipes, data->total - 1);
	apply_redirections(data->cmd->redirections);
	execute_child_command(data->cmd, data->envp, data->internal_env);
}

pid_t	fork_child(t_child_data *data)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_process(data);
	return (pid);
}
