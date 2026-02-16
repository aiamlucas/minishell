/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:59:40 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/25 16:50:18 by lbueno-m         ###   ########.fr       */
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
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	execute_single_process(t_data *data, char *path, int heredoc_fd)
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
		reset_signals();
		free(path);
		apply_redirections(data->commands->redirections);
		execute_child_command(data->commands, data->envp, data->internal_env, heredoc_fd);
		exit(126);
	}
	free(path);
	return (wait_child(pid));
}

static int	execute_builtin_forked(t_data *data, int heredoc_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		reset_signals();
		apply_redirections(data->commands->redirections);
		exit(execute_builtin(data->commands, data->internal_env, heredoc_fd));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_single_command(t_data *data, int heredoc_fd)
{
	char	*path;

	if (!data->commands || !data->commands->argv || !data->commands->argv[0])
		return (1);
	if (is_builtin(data->commands))
	{
		if (must_run_in_parent(data->commands))
			return (execute_builtin(data->commands, data->internal_env, heredoc_fd));
		if (data->commands->redirections)
			return (execute_builtin_forked(data, heredoc_fd));
		return (execute_builtin(data->commands, data->internal_env, heredoc_fd));
	}
	path = find_dir(data->commands->argv[0], data->internal_env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", data->commands->argv[0]);
		return (127);
	}
	return (execute_single_process(data, path, heredoc_fd));
}

int	execute_command(t_data *data, int heredoc_fd)
{
	//(void)heredoc_fd;
	int exit_code;
	
	if (!data->commands)
		return (1);
	if (!data->commands->next)
	{
		if (!heredoc_fd)
			exit_code = execute_single_command(data, heredoc_fd);
	}
	else
	{
		if (!heredoc_fd)
			exit_code = execute_pipeline(data->commands, data->envp, heredoc_fd);
	}
	if (check_signal())
		return (get_signal_exit_code());
	return (exit_code);
}