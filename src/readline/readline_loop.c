/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2025/12/15 00:27:35 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	readline_loop()
{

	char		*prompt;
	t_token		*tokens;
	t_command	*commands;

	while (1)
	{
		prompt = readline("$[ 🛸 ]>");
		if (!prompt)
		{
			printf("exit\n");
			break;
		}
		if (!*prompt)
		{
			free(prompt);
			continue ;
		}
		tokens = lexer(prompt);
		print_tokens(tokens);
		commands = parser(tokens);
		print_commands(commands);
		token_clear(&tokens);
		command_clear(&commands);
		free(prompt);
	}
}
