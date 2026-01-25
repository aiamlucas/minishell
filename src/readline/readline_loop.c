/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/01/25 16:50:49 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_input(char *input, t_data *data)
{
	int			exit_code;

	data->tokens = lexer(input);
	// print_tokens(data->tokens); // for debugging
	data->commands = parser(data->tokens);
	// print_commands(data->commands); // for debugging
	token_clear(&data->tokens);
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
