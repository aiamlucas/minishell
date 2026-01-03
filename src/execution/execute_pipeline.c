/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/03 19:29:28 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	setup_pipes(int **pipes, int i, int total)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < total -1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	child_process(t_command *cmd, int **pipes, int i, int total, char **envp)
{
	char	*path;

	setup_pipes(pipes, i, total);
	close_pipes(pipes, total -1);
	apply_redirections(cmd->redirections);
	if (is_builtin(cmd))
		exit(0);
	path = find_dir(cmd->argv[0], envp);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("minishell");
	exit(126);
}

int	execute_pipeline(t_command *cmds, char **envp)
{
	int		count;
	int		**pipes;
	pid_t	pid;
	pid_t	last_pid;
	int		i;
	int		status;

	i = 0;
	count = count_pipeline_commands(cmds);
	pipes = create_pipes(count -1);
	if (!pipes)
		return (1);
	while (cmds)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			child_process(cmds, pipes, i, count, envp);
		if (i == count -1)
			last_pid = pid;
		cmds = cmds->next;
		i++;
	}
	close_pipes(pipes, count -1);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	free_pipes(pipes, count - 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
