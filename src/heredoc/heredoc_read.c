/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:38 by ssin              #+#    #+#             */
/*   Updated: 2026/02/17 08:33:33 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	read_heredoc(t_redir *redirections, int *fd, struct termios *t_settings)
{
	char	*input_line;

	close(fd[0]);
	while (1)
	{
		input_line = readline("> ");
		if (!input_line || ft_strcmp(input_line, redirections->target) == 0)
		{
			if (input_line)
				free(input_line);
			close(fd[1]);
			tcsetattr(STDIN_FILENO, TCSANOW, t_settings);
			exit(0);
		}
		write(fd[1], input_line, ft_strlen(input_line));
		write(fd[1], "\n", 1);
		free(input_line);
	}
	return (0);
}
