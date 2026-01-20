/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/18 19:58:22 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (true);
	return (false);
}

/*
** Builtins that modify the shell state must run in the parent process.
**
** Example:
**   cd /tmp
**   Running it in a child would not change the shell directory.
*/

bool	must_run_in_parent(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_command *cmd, char **envp)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, envp));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(envp));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, envp));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv));
	return (1);
}
