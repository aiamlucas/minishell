/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/18 11:55:25 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_child_command(t_command *cmd, char **envp, t_env *internal_env)
{
	char		*path;
	struct stat	st;

	if (is_builtin(cmd))
		exit(execute_builtin(cmd, &internal_env, NULL));
	path = find_dir(cmd->argv[0], internal_env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd->argv[0]);
		free(path);
		exit(126);
	}
	execve(path, cmd->argv, envp);
	free(path);
	ft_printf("minishell: %s: %s\n", cmd->argv[0], strerror(errno));
	exit(126);
}
