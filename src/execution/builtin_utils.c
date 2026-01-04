/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 19:18:45 by lbueno-m         ###   ########.fr       */
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
