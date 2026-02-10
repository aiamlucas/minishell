/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:33:18 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/10 12:03:23 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	expanded_length(const char *str, t_env *internal_env, int last_exit)
{
	size_t			total_len;
	size_t			var_len;
	const char		*ptr;
	const char		*var_start;
	t_env			*env_node;
	char			*exit_str;
	char			quote;

	ptr = str;
	total_len = 0;
	quote = '\0';
	while (*ptr)
	{
		if ((*ptr == '\'' || *ptr == '\"') && !quote) // Tracking the quote
		{
			quote = *ptr;
			total_len++;
			ptr++;
			continue ;
		}
		if (*ptr == quote)
		{
			quote = '\0';
			total_len++;
			ptr++;
			continue ;
		}
		if (*ptr != '$')
		{
			total_len++;
			ptr++;
		}
		else
		{
			ptr++;
			if (*ptr == '\0') // Case: $ end of a string
			{
				total_len++;
				break ;
			}
			if (quote == '\'') // don't expand inside single quotes
			{
				total_len++;
				continue ;
			}
			if (*ptr == '?')
			{
				exit_str = ft_itoa(last_exit);
				if (exit_str)
				{
					total_len += ft_strlen(exit_str);
					free(exit_str);
				}
				ptr++;
				continue ;
			}
			// Case: $ followd by non-variable char
			if (!(ft_isalpha(*ptr) || *ptr == '_'))
			{
				total_len++;
				continue ;
			}
			// Case $VAR -> find variable length
			var_start = ptr;
			var_len = 0;
			while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
			{
				ptr++;
				var_len++;
			}
			env_node = internal_env;
			while (env_node)
			{
				if (ft_strncmp(env_node->key, var_start, var_len) == 0 && env_node->key[var_len] == '\0')
				{
					total_len += ft_strlen(env_node->value);
					break ;
				}
				env_node = env_node->next;
			}
		}
	}
	return (total_len);
}

static char	*expand_variable(const char *str, t_env *internal_env, int last_exit, size_t len)
{
	const char	*ptr;
	const char	*var_start;
	const char	*value;
	t_env		*env_node;
	size_t		total_len;
	size_t		var_len;
	size_t		i;
	char		*result;
	char		*exit_str;
	char		quote;

	ptr = str;
	quote = '\0';
	total_len = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (*ptr)
	{
		if ((*ptr =='\'' || *ptr == '\"') && !quote) // tracking quote
		{
			quote = *ptr;
			result[total_len++] = *ptr++;
			continue ;
		}
		if (*ptr == quote)
		{
			quote = '\0';
			result[total_len++] = *ptr++;
			continue ;
		}
		if (*ptr != '$')
		{
			result[total_len] = *ptr;
			total_len++;
			ptr++;
		}
		else
		{
			ptr++;
			// Case: $ at end of string
			if (*ptr == '\0')
			{
				result[total_len++] = '$';
				result[total_len] = '\0';
				return (result);
			}
			if (quote == '\'')
			{
				result[total_len++] = '$';
				continue ;
			}
			if (*ptr == '?')
			{
				exit_str = ft_itoa(last_exit);
				if (exit_str)
				{
					i = 0;
					while (exit_str[i])
						result[total_len++] = exit_str[i++];
					free(exit_str);
				}
				ptr++;
				continue ;
			}
			// Case: $ followed by non-variable char
			if (!(ft_isalpha(*ptr) || *ptr == '_'))
			{
				result[total_len++] = '$';
				continue ;
			}
			// Case: $VAR -> expand variable
			var_start = ptr;
			var_len = 0;
			while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
			{
				ptr++;
				var_len++;
			}
			// Search for variable in enviroment and copy value
			env_node = internal_env;
			while (env_node)
			{
				if (ft_strncmp(env_node->key, var_start, var_len) == 0 && (env_node->key)[var_len] == '\0')
				{
					value = env_node->value;
					while (*value)
					{
						result[total_len++] = *value;
						value++;
					}
					break ;
				}
				env_node = env_node->next;
			}
		}
	}
	result[total_len] = '\0';
	return (result);
}

bool	expand_tokens(t_token *tokens, t_env *internal_env, int last_exit)
{
	t_token		*current;
	char		*expanded;
	size_t		expanded_len;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded_len = expanded_length(current->value, internal_env, last_exit);
			expanded = expand_variable(current->value, internal_env, last_exit, expanded_len);
			if (!expanded)
				return (false);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
	return (true);
}
