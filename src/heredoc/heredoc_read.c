/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:38 by ssin              #+#    #+#             */
/*   Updated: 2026/02/27 16:10:32 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_input(t_data *data, int *fd)
{
	close(fd[1]);
	tcsetattr(STDIN_FILENO, TCSANOW, data->t_settings);
}

int	read_heredoc(t_data *data, int *fd)
{
	char	*input_line;

	close(fd[0]);
	while (1)
	{
		input_line = readline("> ");
		if (ft_strchr(input_line, '$'))
			input_line = expand_string(input_line, data->internal_env,
					data->last_exit);
		if (!input_line)
		{
			check_input(data, fd);
			exit (1);
		}
		if (ft_strcmp(input_line, data->commands->redirections->target) == 0)
		{
			check_input(data, fd);
			free(input_line);
			exit (0);
		}
		write(fd[1], input_line, ft_strlen(input_line));
		write(fd[1], "\n", 1);
		free(input_line);
	}
	return (0);
}
