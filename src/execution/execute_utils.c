/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:51:23 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/24 15:32:48 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// temporary build in
int	is_bultin(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		ft_printf("test: guard buildin\n");
		return (0);

	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ft_printf("test: running pwd builtin\n");
		return (1);
	}
}
