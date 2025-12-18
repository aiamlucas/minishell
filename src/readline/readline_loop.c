/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2025/12/18 12:47:04 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	readline_loop(void)
{
	char	*input;
	t_token	*tokens;
	t_command	*commands;

	while (1)
	{
		input = readline("$[ 🛸 ]>");
		if (input && ft_strlen(input))
			add_history(input);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		tokens = lexer(input);
		print_tokens(tokens);
		commands = parser(tokens);
		print_commands(commands);
		token_clear(&tokens);
		command_clear(&commands);
		free(input);
	}
}
