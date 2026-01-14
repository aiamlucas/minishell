/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/01/14 19:06:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_input(char *input, char **envp)
{
	t_token		*tokens;
	t_command	*commands;
	int			exit_code;

	tokens = lexer(input);
	// print_tokens(tokens); // for debugging
	commands = parser(tokens);
	// print_commands(commands); // for debugging
	token_clear(&tokens);
	exit_code = execute_command(commands, envp);
	command_clear(&commands);
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

static bool	handle_input_line(char *input, char **envp)
{
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
	process_input(input, envp);
	free(input);
	return (true);
}

void	readline_loop(char **envp)
{
	char		*input;

	while (1)
	{
		reset_signal();
		input = readline("$[ 🛸 ]>");
		if (!handle_input_line(input, envp))
			break ;
	}
}
