/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/02/11 11:32:35 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_input(char *input, t_data *data)
{
	int			fd[2];
	int			exit_code;
	char		buffer[1024];

	data->tokens = lexer(input);
	//printf("tokens\n");
	//print_tokens(data->tokens);
	//printf("\n after expansion: \n");
	expand_tokens(data->tokens, data->internal_env, data->last_exit);
	//print_tokens(data->tokens); // for debugging
	data->commands = parser(data->tokens);
	// print_commands(data->commands); // for debugging
	token_clear(&data->tokens);
	if (pipe(fd) == -1)
		ft_printf("heredoc error pipe\n");
		// return or exit
	handle_heredoc(data, fd);
	ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
	if (bytes_read > 0) {
		buffer[bytes_read] = '\0';
		printf("Read: %s\n", buffer);
	}
	exit_code = execute_command(data);
	command_clear(&data->commands);
	if (check_signal())
		exit_code = get_signal_exit_code();
	return (exit_code);
}

static bool	skip_input(char *input)
{
	if (!*input || !ft_strlen(input))
		return (true);
	return (false);
}

static void	handle_signal_cleanup(char *input)
{
	reset_signal();
	free(input);
}

static bool	handle_input_line(char *input, t_data *data)
{
	int	exit_code;

	if (!input)
	{
		printf("exit\n");
		return (false);
	}
	if (check_signal())
	{
		handle_signal_cleanup(input);
		return (true);
	}
	if (skip_input(input))
	{
		free(input);
		return (true);
	}
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
		input = readline("$[ 🛸 ]>");
		if (!handle_input_line(input, data))
			break ;
	}
}
