/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:33:18 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/23 19:45:24 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*init_expand(t_expand *exp, size_t len,
							size_t *i, char *quote)
{
	exp->result = malloc(len + 1);
	if (!exp->result)
		return (NULL);
	*i = 0;
	*quote = '\0';
	exp->i = i;
	exp->quote = quote;
	return (exp->result);
}

static char	*expand_variable(const char *str, t_env *internal_env,
								int last_exit, size_t len)
{
	const char	*ptr;
	size_t		i;
	char		quote;
	t_expand	exp;

	if (!init_expand(&exp, len, &i, &quote))
		return (NULL);
	ptr = str;
	while (*ptr)
	{
		if (write_non_dollar(&ptr, &exp))
			continue ;
		if (!write_dollar(&ptr, &exp, last_exit))
			break ;
		if (!(ft_isalpha(*ptr) || *ptr == '_'))
		{
			exp.result[i++] = '$';
			ptr++;
			continue ;
		}
		copy_var_value(&ptr, &exp, internal_env);
	}
	exp.result[i] = '\0';
	return (exp.result);
}

bool	expand_tokens(t_token *tokens, t_env *internal_env, int last_exit)
{
	t_token	*current;
	char	*expanded;
	size_t	expanded_len;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded_len = expanded_length(current->value, internal_env,
					last_exit);
			expanded = expand_variable(current->value, internal_env, last_exit,
					expanded_len);
			if (!expanded)
				return (false);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
	return (true);
}
