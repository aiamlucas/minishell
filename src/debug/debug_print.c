/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:24:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/25 20:35:28 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		ft_printf("[%s]", current->value);
		if (current->next)
			ft_printf("->");
		current = current->next;
	}
	ft_printf("->NULL\n");
}

void	print_redirections(t_redir *redirections)
{
	t_redir	*current;

	current = redirections;
	if (!redirections)
	{
		ft_printf("NULL");
		return ;
	}
	ft_printf("[");
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			ft_printf("< %s", current->file);
		else if (current->type == TOKEN_REDIR_OUT)
			ft_printf("> %s", current->file);
		else if (current->type == TOKEN_REDIR_APPEND)
			ft_printf(">> %s", current->file);
		else if (current->type == TOKEN_HEREDOC)
			ft_printf("<< %s", current->file);
		if (current->next)
			ft_printf(", ");
		current = current->next;
	}
	ft_printf("]");
}

static void	print_argv(char *argv[])
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		ft_printf("\"%s\"", argv[i]);
		if (argv[i + 1])
			ft_printf(", ");
		i++;
	}
}

void	print_commands(t_command *commands)
{
	t_command	*current;
	int			command_num;

	if (!commands)
	{
		ft_printf("no commands\n");
		return ;
	}
	current = commands;
	command_num = 1;
	while (current)
	{
		ft_printf("cmd%d->argv = [", command_num);
		print_argv(current->argv);
		ft_printf(", NULL]\n");
		ft_printf("cmd%d->redirections = ", command_num);
		print_redirections(current->redirections);
		ft_printf("\n");
		current = current->next;
		command_num++;
	}
	ft_printf("\n");
}

void	print_env_list(t_env *list)
{
	while (list)
	{
		if (list->value)
			ft_printf("%s=%s\n", list->key, list->value);
		else
			ft_printf("%s=\n", list->key);
		list = list->next;
	}
}
