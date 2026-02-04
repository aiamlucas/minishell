/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/02/04 14:53:36 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_input(char *input, t_data *data)
{
	int			exit_code;

	data->tokens = lexer(input);
	printf("tokens\n");
	print_tokens(data->tokens);
	printf("\n after expansion: \n");
	expand_tokens(data->tokens, data->internal_env, data->last_exit);
	print_tokens(data->tokens); // for debugging
	data->commands = parser(data->tokens);
	// print_commands(data->commands); // for debugging
	token_clear(&data->tokens);
	exit_code = execute_command(data);
	command_clear(&data->commands);
	if (check_signal())
		exit_code = get_signal_exit_code();
	return (exit_code);
}

static void	handle_signal_cleanup(char *input)
{
	reset_signal();
	free(input);
}

static int	check_input_validation(char *input, t_data *data)
{
	if (!input)
		return (-1);
	if (check_signal())
	{
		handle_signal_cleanup(input);
		return (1);
	}
	if (is_empty_input(input))
	{
		free(input);
		return (1);
	}
	if (has_unclosed_quotes(input))
	{
		ft_printf("minishell: syntax error: unclosed quote\n");
		free(input);
		data->last_exit = 2;
		return (1);
	}
	return (0);
}

static bool	handle_input_line(char *input, t_data *data)
{
	int	validation;
	int	exit_code;

	validation = check_input_validation(input, data);
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
		input = readline("$[ 🛸 ]>");
		if (!handle_input_line(input, data))
			break ;
	}
}
