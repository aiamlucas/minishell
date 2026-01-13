/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:51:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/26 15:06:21 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipeline_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (NULL);
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
