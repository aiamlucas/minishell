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

static void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("[%s]", current->value);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("->NULL\n");
}

void	readline_loop(void)
{
	char	*input;
	t_token	*tokens;

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
		token_clear(&tokens);
		free(input);
	}
}
