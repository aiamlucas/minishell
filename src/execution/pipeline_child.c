/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:27:12 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/06 14:32:38 by ssin             ###   ########.fr       */
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
	setup_pipes(data);
	close_pipes(data->pipes, data->total - 1);
	apply_redirections(data->cmd->redirections);
	execute_child_command(data->cmd, data->envp, NULL);
}

pid_t	fork_child(t_child_data *data)
{
	pid_t			pid;

	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	if (pid == CHILD)
		child_process(data);
	return (pid);
}
