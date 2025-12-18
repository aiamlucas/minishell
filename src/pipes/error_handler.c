/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:57 by ssin              #+#    #+#             */
/*   Updated: 2025/12/17 13:20:58 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	error_handler(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_dir(char **dir1, char **dir2, char *msg)
{
	free(*dir1);
	free(*dir2);
	error_handler(msg);
}

void	free_memo(char **memo)
{
	int	i;

	i = 0;
	if (!memo)
		return ;
	while (memo[i])
	{
		free(memo[i]);
		i++;
	}
	free(memo);
}

char	*free_return(char **cmd, char **env, char *path)
{
	free_memo(cmd);
	free_memo(env);
	return (path);
}
