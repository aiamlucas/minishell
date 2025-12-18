/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:09:13 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/18 15:41:23 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	print_test_result(const char *test_name, int passed)
{
	if (passed)
		printf(GREEN "OK - %s\n" RESET, test_name);
	else
		printf(RED "KO - %s\n" RESET, test_name);
}

void	print_test_header(const char *category)
{
	printf("\n%s\n", category);
}

int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

int	count_commands(t_command *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

int	count_redirections(t_redir *redirections)
{
	int	count;

	count = 0;
	while (redirections)
	{
		count++;
		redirections = redirections->next;
	}
	return (count);
}
