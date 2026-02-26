/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:29:01 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/26 11:30:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_input(char *input, t_data *data)
{
	int			exit_code;

	data->tokens = lexer(input);
	printf("tokens\n");
	print_tokens(data->tokens);
	printf("\n after expansion: \n");
	expand_tokens(data->tokens, data->internal_env, data->last_exit);
	print_tokens(data->tokens);
	printf("\n after quote removal: \n");
	remove_quotes(data->tokens);
	print_tokens(data->tokens);
	data->commands = parser(data->tokens);
	print_commands(data->commands); // for debugging
	token_clear(&data->tokens);
	exit_code = execute_command(data);
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
