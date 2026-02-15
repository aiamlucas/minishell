/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:08:03 by ssin              #+#    #+#             */
/*   Updated: 2026/02/15 18:30:47 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "minishell_macros.h"

static char	*skip_quoted_section(char *input, char quote_char)
{
	input++;
	while (*input && *input != quote_char)
		input++;
	if (*input == quote_char)
		input++;
	return (input);
}

char	*get_word(char *input)
{
	char	*start;
	char	*current;
	int		len;
	char	*word;

	start = input;
	current = input;
	while (*current && !ft_isspace(*current)
		&& *current != C_PIPE
		&& *current != C_RED_IN
		&& *current != C_RED_OUT)
	{
		if (*current == C_S_QUOTE)
			current = skip_quoted_section(current, C_S_QUOTE);
		else if (*current == C_D_QUOTE)
			current = skip_quoted_section(current, C_D_QUOTE);
		else
			current++;
	}
	len = current - start;
	word = ft_substr(start, 0, len);
	return (word);
}

char	*get_token_operator(char *input)
{
	if (*input == C_PIPE)
		return (STR_PIPE);
	else if (*input == C_RED_IN)
	{
		if (*(input + 1) == C_RED_IN)
			return (STR_HEREDOC);
		return (STR_RED_IN);
	}
	else if (*input == C_RED_OUT)
	{
		if (*(input + 1) == C_RED_OUT)
			return (STR_RED_APP);
		return (STR_RED_OUT);
	}
	else
		return (get_word(input));
}

t_token_type	get_type(char *input)
{
	if (!ft_strncmp(input, STR_PIPE, ft_strlen(STR_PIPE)))
		return (TOKEN_PIPE);
	if (!ft_strncmp(input, STR_RED_IN, ft_strlen(STR_RED_IN)))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(input, STR_HEREDOC, ft_strlen(STR_HEREDOC)))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(input, STR_RED_OUT, ft_strlen(STR_RED_OUT)))
		return (TOKEN_REDIR_OUT);
	if (!ft_strncmp(input, STR_RED_APP, ft_strlen(STR_RED_APP)))
		return (TOKEN_REDIR_APPEND);
	return (TOKEN_WORD);
}

t_token	*lexer(char *input)
{
	t_token			*tokens_list;
	char			*operator;
	t_token_type	type;
	int				len;

	len = 0;
	tokens_list = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		operator = get_token_operator(input);
		len = ft_strlen(operator);
		type = get_type(input);
		input += len;
		token_add_back(&tokens_list, new_token(operator, type));
		if (type == TOKEN_WORD)
			free(operator);
	}
	return (tokens_list);
}
