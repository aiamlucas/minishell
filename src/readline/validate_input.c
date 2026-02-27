/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:38:22 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/04 14:54:59 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_empty_input(char *input)
{
	if (!*input || !ft_strlen(input))
		return (true);
	return (false);
}

bool	has_unclosed_quotes(char *input)
{
	char	quote;

	quote = '\0';
	while (*input)
	{
		if ((*input == '\'' || *input == '\"') && !quote)
			quote = *input;
		else if (*input == quote)
			quote = '\0';
		input++;
	}
	return (quote != '\0');
}
