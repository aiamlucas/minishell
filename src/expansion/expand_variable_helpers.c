/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:46:24 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/23 19:47:13 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	write_non_dollar(const char **ptr, t_expand *exp)
{
	if ((**ptr == '\'' || **ptr == '\"') && !*exp->quote)
	{
		*exp->quote = **ptr;
		exp->result[(*exp->i)++] = *(*ptr)++;
		return (true);
	}
	if (**ptr == *exp->quote)
	{
		*exp->quote = '\0';
		exp->result[(*exp->i)++] = *(*ptr)++;
		return (true);
	}
	if (**ptr != '$')
	{
		exp->result[(*exp->i)++] = *(*ptr)++;
		return (true);
	}
	return (false);
}

void	write_exit_status(t_expand *exp, int last_exit)
{
	char	*exit_str;
	size_t	j;

	exit_str = ft_itoa(last_exit);
	if (exit_str)
	{
		j = 0;
		while (exit_str[j])
			exp->result[(*exp->i)++] = exit_str[j++];
		free(exit_str);
	}
}

bool	write_dollar(const char **ptr, t_expand *exp, int last_exit)
{
	(*ptr)++;
	if (**ptr == '\0')
	{
		exp->result[(*exp->i)++] = '$';
		return (false);
	}
	if (*exp->quote == '\'')
	{
		exp->result[(*exp->i)++] = '$';
		return (true);
	}
	if (**ptr == '?')
	{
		write_exit_status(exp, last_exit);
		(*ptr)++;
		return (true);
	}
	return (true);
}

void	copy_var_value(const char **ptr, t_expand *exp, t_env *env)
{
	const char	*start;
	size_t		var_len;
	const char	*value;

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
		{
			value = env->value;
			while (*value)
			{
				exp->result[(*exp->i)++] = *value++;
			}
			break ;
		}
		env = env->next;
	}
}
