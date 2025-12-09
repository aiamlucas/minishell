#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/minishell_macros.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *prompt;

	while (1)
	{
		prompt = readline("$[ 🛸 ]>");
		//printf("%s\n", prompt);
		//if (ft_strncmp(prompt, "exit"))
		//	exit(EXIT_SUCCESS);
	}
	return (0);
}
