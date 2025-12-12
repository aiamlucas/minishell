/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:08:03 by ssin              #+#    #+#             */
/*   Updated: 2025/12/12 18:08:05 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_word(char *input)
{
	char	*start;
	int		len;
	char	*word;

	start = input;
	while (*input && !ft_isspace(*input) && *input != '|' && *input != '<'
		&& *input != '>' && *input != '"' && *input != '\'')
		input++;
	len = input - start;
	word = ft_substr(start, 0, len);
	return (word);
}

char	*get_token_metachar(char *input)
{
	if (*input == PIPE)
		return ("|");
	else if (*input == RED_IN)
	{
		if (*(input + 1) == RED_IN)
			return ("<<");
		return ("<");
	}
	else if (*input == RED_OUT)
	{
		if (*(input + 1) == RED_OUT)
			return (">>");
		return (">");
	}
	else if (*input == S_QUOTE)
		return ("'");
	else if (*input == D_QUOTE)
		return ("\"");
	else if (*input == EXP)
		return ("$");
	else
		return (get_word(input));
}

t_token_type	get_type(char input)
{
	(void)input;
	return (TOKEN_PIPE);
}

t_token	*lexer(char *input)
{
	t_token			*tokens_list;
	char			*metacharacter;
	int				len;
	t_token_type	type;

	len = 0;
	tokens_list = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		metacharacter = get_token_metachar(input);
		len = ft_strlen(metacharacter);
		input += len;
		type = get_type(*input);
		token_add_back(&tokens_list, new_token(metacharacter, type));
		if (type == TOKEN_WORD)
			free(metacharacter);
	}
	return (tokens_list);
}
