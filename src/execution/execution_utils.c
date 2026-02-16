/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/13 19:05:44 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_child_command(t_command *cmd, char **envp, t_env *internal_env, int heredoc_fd)
{
	char	*path;

	if (is_builtin(cmd))
		exit(execute_builtin(cmd, internal_env, heredoc_fd));
	path = find_dir(cmd->argv[0], internal_env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("minishell");
	exit(126);
}
