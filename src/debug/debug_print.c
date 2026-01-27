/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:24:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/15 12:28:48 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void print_tokens(t_token *tokens)
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

void	print_redirections(t_redir *redirections)
{
	t_redir	*current = redirections;

	if (!redirections)
	{
		printf("NULL");
		return ;
	}
	printf("[");
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			printf("< %s", current->file);
		else if (current->type == TOKEN_REDIR_OUT)
			printf("> %s", current->file);
		else if (current->type == TOKEN_REDIR_APPEND)
			printf(">> %s", current->file);
		else if (current->type == TOKEN_HEREDOC)
			printf("<< %s", current->file);
		if (current->next)
			printf(", ");
		current = current->next;
	}
	printf("]");
}

void	print_commands(t_command *commands)
{
	t_command	*current = commands;
	int			command_num;
	int			i;

	command_num = 1;
	i = 0;

	if (!commands)
	{
		printf("no commands\n");
		return ;
	}
	while (current)
	{
		printf("cmd%d->argv = [", command_num);

		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				printf("\"%s\"", current->argv[i]);
				if (current->argv[i + 1])
					printf(", ");
				i++;
			}
		}
		printf(", NULL]\n");
		printf("cmd%d->redirections = ", command_num);
		print_redirections(current->redirections);
		printf("\n");
		current = current->next;
		command_num++;
	}
	printf("\n");
}

void	print_env_list(t_env *list)
{
	while (list)
	{
		printf("%s=%s\n", (char *)list->key, (char *)list->value);
		list = list->next;
	}
}
