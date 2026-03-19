/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:24:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/19 11:55:06 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_token *tokens)
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

void	print_redirections(t_redir *redirections)
{
	t_redir	*current;

	current = redirections;
	if (!redirections)
	{
		printf("NULL");
		return ;
	}
	printf("[");
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			printf("< %s", current->target);
		else if (current->type == TOKEN_REDIR_OUT)
			printf("> %s", current->target);
		else if (current->type == TOKEN_REDIR_APPEND)
			printf(">> %s", current->target);
		else if (current->type == TOKEN_HEREDOC)
			printf("<< %s", current->target);
		if (current->next)
			printf(", ");
		current = current->next;
	}
	printf("]");
}

static void	print_argv(char *argv[])
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		printf("\"%s\"", argv[i]);
		if (argv[i + 1])
			printf(", ");
		i++;
	}
}

void	print_commands(t_command *commands)
{
	t_command	*current;
	int			command_num;

	if (!commands)
	{
		printf("no commands\n");
		return ;
	}
	current = commands;
	command_num = 1;
	while (current)
	{
		printf("cmd%d->argv = [", command_num);
		print_argv(current->argv);
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
		if (list->value)
			printf("%s=%s\n", list->key, list->value);
		else
			printf("%s=\n", list->key);
		list = list->next;
	}
}
