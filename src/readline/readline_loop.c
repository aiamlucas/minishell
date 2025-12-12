/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2025/12/11 19:10:58 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_tokens(t_token *tokens)
{
	t_token	*current = tokens;

	while (current)
	{
		printf("[%s]", current->value);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("->NULL\n");
}

void	readline_loop()
{
	while (1)
	{
		char	*prompt;
		t_token	*tokens;

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
		token_clear(&tokens);
		free(prompt);
	}
}
