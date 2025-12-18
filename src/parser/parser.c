/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:48:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/17 16:16:28 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_redirection(t_token_type type)
{
	return (
		type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND
		|| type == TOKEN_HEREDOC
	);
}

static bool	handle_redirection(t_command **current_command, t_token **redir_arg)
{
	t_token_type	redir_type;
	t_redir			*new_redir;	

	redir_type = (*redir_arg)->type;
	*redir_arg = (*redir_arg)->next;
	if (!*redir_arg || (*redir_arg)->type != TOKEN_WORD)
	{
		printf("error --> redirection?\n");
		return (false);
	}
	if (!*current_command)
		*current_command = command_new();
	new_redir = redir_new(redir_type, (*redir_arg)->value);
	redir_add_back(&(*current_command)->redirections, new_redir);
	return (true);
}

static void	add_to_argv(t_command *cmd, char *word)
{
	int	size;

	size = 0;
	if (cmd->argv)
		while (cmd->argv[size])
			size++;
	cmd->argv = realloc(cmd->argv, sizeof(char *) * (size + 2));
	cmd->argv[size] = ft_strdup(word);
	cmd->argv[size + 1] = NULL;
}

t_command	*parser(t_token *tokens)
{
	t_command	*command_list;
	t_command	*current_command;
	t_token		*current_token;

	command_list = NULL;
	current_command = NULL;
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == TOKEN_WORD)
		{
			if (!current_command)
				current_command = command_new();
			add_to_argv(current_command, current_token->value);
		}
		else if (current_token->type == TOKEN_PIPE)
		{
			command_add_back(&command_list, current_command);
			current_command = NULL;
		}
		else if (is_redirection(current_token->type))
		{
			if (!handle_redirection(&current_command, &current_token))
			{
				command_clear(&command_list);
				command_clear(&current_command);
				return (NULL);
			}
		}
		current_token = current_token->next;
	}
	if (current_command)
		command_add_back(&command_list, current_command);
	return (command_list);
}
