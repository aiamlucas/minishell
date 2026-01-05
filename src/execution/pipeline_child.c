/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:27:12 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/05 18:56:53 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_pipes(int **pipes, int i, int total)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < total - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	child_process(t_child_data *data)
{
	char	*path;

	setup_pipes(data->pipes, data->i, data->total);
	close_pipes(data->pipes, data->total - 1);
	apply_redirections(data->cmd->redirections);
	if (is_builtin(data->cmd))
		exit(execute_builtin(data->cmd, data->envp));
		exit(0);
	path = find_dir(data->cmd->argv[0], data->envp);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", data->cmd->argv[0]);
		exit(127);
	}
	execve(path, data->cmd->argv, data->envp);
	perror("minishell");
	exit(126);
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
