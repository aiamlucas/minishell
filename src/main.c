#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/minishell.h"

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

int	main(void)
{
	char	*prompt;
	t_token	*tokens;

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
		token_clear(&tokens);
		free(prompt);
	}
	return (0);
}
