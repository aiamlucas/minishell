/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:38 by ssin              #+#    #+#             */
/*   Updated: 2026/02/11 11:08:31 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	read_heredoc(t_redir redirections, int *fd)
{
	char	*input_line;

	while (1)
	{
		input_line = readline("> ");
		if (input_line == redirections->target)
			break ;
	}
	return (0);
}
