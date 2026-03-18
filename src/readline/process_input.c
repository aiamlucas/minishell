/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:29:01 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/18 19:59:12 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_input(char *input, t_data *data)
{
	int			exit_code;

	data->tokens = lexer(input);
	if (!expand_tokens(data->tokens, data->internal_env, data->last_exit))
	{
		token_clear(&data->tokens);
		return (1);
	}
	if (!remove_quotes(data->tokens))
	{
		token_clear(&data->tokens);
		return (1);
	}
	data->commands = parser(data->tokens);
	token_clear(&data->tokens);
	if (data->commands)
	{
		exit_code = process_all_heredocs(data);
		if (exit_code == 0 && !g_signal_received)
			exit_code = execute_command(data);
	}
	command_clear(&data->commands);
	if (check_signal())
		exit_code = get_signal_exit_code();
	return (exit_code);
}

int	check_input_validation(char *input)
{
	if (!input)
		return (-1);
	if (is_empty_input(input))
	{
		free(input);
		return (1);
	}
	return (0);
}
