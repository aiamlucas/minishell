/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:29:38 by ssin              #+#    #+#             */
/*   Updated: 2026/03/09 18:49:31 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_input(t_data *data, int *fd)
{
	close(fd[1]);
	tcsetattr(STDIN_FILENO, TCSANOW, data->t_settings);
}

int	found_delimiter(char *input_line, t_data *data, int *fd)
{
	if (ft_strcmp(input_line, data->commands->redirections->target) == 0)
	{
		check_input(data, fd);
		free(input_line);
		return (1);
	}
	return (0);
}

void	write_input(int *fd, char *input_line)
{
	write(fd[1], input_line, ft_strlen(input_line));
	write(fd[1], "\n", 1);
	free(input_line);
}

int	read_heredoc(t_data *data, int *fd)
{
	char	*input_line;
	char	*expanded;

	close(fd[0]);
	while (1)
	{
		input_line = readline("> ");
		if (!input_line)
		{
			check_input(data, fd);
			exit (0);
		}
		if (data->commands->redirections->should_expand
			&& ft_strchr(input_line, '$'))
		{
			expanded = expand_string(input_line, data->internal_env,
					data->last_exit);
			free(input_line);
			input_line = expanded;
		}
		if (found_delimiter(input_line, data, fd))
			exit (0);
		write_input(fd, input_line);
	}
	return (0);
}
