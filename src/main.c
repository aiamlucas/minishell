#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/minishell_macros.h"


static void print_split(char **split)
{
	int i = 0;

	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *prompt;

	while (1)
	{
		prompt = readline("$[ 🛸 ]>");
		char delimiter = ' ';
		int i = 0;

		char **splited = ft_split(prompt, delimiter);
		print_split(splited);
	}
	return (0);
}
