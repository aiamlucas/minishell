/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:59:40 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/03 19:47:56 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static bool	handle_single_builtin(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	if (is_builtin(cmd))
		return (true);
	return (false);
}

static int	execute_single_process(t_command *cmd, char *path, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		apply_redirections(cmd->redirections);
		execve(path, cmd->argv, envp);
		perror("minishell");
		exit(126);
	}
	free(path);
	return (wait_child(pid));
}

int	execute_single_command(t_command *cmd, char **envp)
{
	char	*path;

	if (handle_single_builtin(cmd))
		return (0);
	path = find_dir(cmd->argv[0], envp);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		return (127);
	}
	return (execute_single_process(cmd, path, envp));
}

int	execute_command(t_command *commands, char **envp)
{
	if (!commands)
		return (-1);
	if (!commands->next)
		return (execute_single_command(commands, envp));
	else
		return (execute_pipeline(commands, envp));
}
