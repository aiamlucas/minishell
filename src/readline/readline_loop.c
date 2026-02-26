/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/02/26 13:12:15 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*join_with_newline(char *line, char *temp)
{
	char	*with_newline;
	char	*joined;

	with_newline = ft_strjoin(line, "\n");
	if (!with_newline)
		return (NULL);
	joined = ft_strjoin(with_newline, temp);
	free(with_newline);
	return (joined);
}

static char	*read_continuation_line(char *current_line)
{
	char	*temp;
	char	*result;

	temp = readline("> ");
	if (!temp)
		return (NULL);
	if (check_signal())
	{
		free(temp);
		return (NULL);
	}
	result = join_with_newline(current_line, temp);
	free(temp);
	return (result);
}

static char	*readline_with_continuation(const char *input)
{
	char	*line;
	char	*new_line;

	line = readline(input);
	if (!line)
		return (NULL);
	while (has_unclosed_quotes(line))
	{
		if (check_signal())
		{
			free(line);
			return (NULL);
		}
		new_line = read_continuation_line(line);
		free(line);
		if (!new_line)
			return (NULL);
		line = new_line;
	}
	return (line);
}

static bool	handle_input_line(char *input, t_data *data)
{
	int	validation;
	int	exit_code;

	if (check_signal())
	{
		data->last_exit = get_signal_exit_code();
		// if (input)
		// 	free(input);
		// return (true);
	}
	validation = check_input_validation(input);
	if (validation == -1)
	{
		ft_printf("exit\n");
		return (false);
	}
	if (validation == 1)
		return (true);
	add_history(input);
	exit_code = process_input(input, data);
	data->last_exit = exit_code;
	free(input);
	return (true);
}

void	readline_loop(t_data *data)
{
	char		*input;

	while (1)
	{
		reset_signal();
		input = readline_with_continuation("$[ 🛸 ]>");
		if (!handle_input_line(input, data))
			break ;
	}
}
