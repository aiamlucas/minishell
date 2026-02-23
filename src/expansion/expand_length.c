/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:24:52 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/23 19:28:45 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	handle_non_dollar(const char **ptr, size_t *total_len, char *quote)
{
	if ((**ptr == '\'' || **ptr == '\"') && !*quote)
	{
		*quote = **ptr;
		(*total_len)++;
		(*ptr)++;
		return (true);
	}
	if (**ptr == *quote)
	{
		*quote = '\0';
		(*total_len)++;
		(*ptr)++;
		return (true);
	}
	if (**ptr != '$')
	{
		(*total_len)++;
		(*ptr)++;
		return (true);
	}
	return (false);
}

static bool	handle_dollar(const char **ptr, size_t *total_len, char *quote,
							int last_exit)
{
	char	*exit_str;

	(*ptr)++;
	if (**ptr == '\0')
	{
		(*total_len)++;
		return (false);
	}
	if (*quote == '\'')
	{
		(*total_len)++;
		return (true);
	}
	if (**ptr == '?')
	{
		exit_str = ft_itoa(last_exit);
		if (exit_str)
		{
			(*total_len) += ft_strlen(exit_str);
			free(exit_str);
		}
		(*ptr)++;
		return (true);
	}
	return (true);
}

static size_t	find_var_len(const char **ptr, t_env *env)
{
	const char	*start;
	size_t		var_len;

	start = *ptr;
	var_len = 0;
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
	{
		(*ptr)++;
		var_len++;
	}
	while (env)
	{
		if (ft_strncmp(env->key, start, var_len) == 0
			&& (env->key)[var_len] == '\0')
			return (ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

size_t	expanded_length(const char *str, t_env *internal_env,
								int last_exit)
{
	size_t		total_len;
	const char	*ptr;
	char		quote;

	ptr = str;
	total_len = 0;
	quote = '\0';
	while (*ptr)
	{
		if (handle_non_dollar(&ptr, &total_len, &quote))
			continue ;
		if (!handle_dollar(&ptr, &total_len, &quote, last_exit))
			break ;
		if (!(ft_isalpha(*ptr) || *ptr == '_'))
		{
			total_len++;
			ptr++;
			continue ;
		}
		total_len += find_var_len(&ptr, internal_env);
	}
	return (total_len);
}
