/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:05:13 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/11 15:56:20 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	calculate_length_without_quotes(const char *str)
{
	char	quote;
	size_t	len;

	len = 0;
	quote = '\0';
	while (*str)
	{
		if ((*str == C_S_QUOTE || *str == C_D_QUOTE) && !quote)
			quote = *str;
		else if (*str == quote)
			quote = '\0';
		else
			len++;
		str++;
	}
	return (len);
}

char	*remove_quote_chars(const char *str)
{
	char	quote;
	size_t	i;
	size_t	len;
	char	*result;

	i = 0;
	quote = '\0';
	len = calculate_length_without_quotes(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (*str)
	{
		if ((*str == C_S_QUOTE || *str == C_D_QUOTE) && !quote)
			quote = *str;
		else if (*str == quote)
			quote = '\0';
		else
			result[i++] = *str;
		str++;
	}
	result[i] = '\0';
	return (result);
}

bool	remove_quotes(t_token *tokens)
{
	t_token	*current;
	char	*new_value;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			new_value = remove_quote_chars(current->value);
			if (!new_value)
				return (false);
			free(current->value);
			current->value = new_value;
		}
		current = current->next;
	}
	return (true);
}
