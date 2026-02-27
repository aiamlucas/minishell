/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:46:24 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/27 19:24:48 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	update_state(t_expand_state *state, char c)
{
	if (*state == EXPAND_NORMAL && c == '\'')
	{
		*state = EXPAND_SINGLE;
		return (true);
	}
	if (*state == EXPAND_NORMAL && c == '\"')
	{
		*state = EXPAND_DOUBLE;
		return (true);
	}
	if (*state == EXPAND_SINGLE && c == '\'')
	{
		*state = EXPAND_NORMAL;
		return (true);
	}
	if (*state == EXPAND_DOUBLE && c == '\"')
	{
		*state = EXPAND_NORMAL;
		return (true);
	}
	return (false);
}

bool	build_char(const char **ptr, t_expand *exp)
{
	if (update_state(exp->state, **ptr) || **ptr != '$')
	{
		exp->result[(*exp->position)++] = *(*ptr)++;
		return (true);
	}
	return (false);
}

static void	build_exit_status(t_expand *exp, int last_exit)
{
	char	*exit_str;
	size_t	j;

	exit_str = ft_itoa(last_exit);
	if (exit_str)
	{
		j = 0;
		while (exit_str[j])
			exp->result[(*exp->position)++] = exit_str[j++];
		free(exit_str);
	}
}

t_dollar_act	build_dollar(const char **ptr, t_expand *exp, int last_exit)
{
	(*ptr)++;
	if (**ptr == '\0')
	{
		exp->result[(*exp->position)++] = '$';
		return (D_STOP);
	}
	if (*exp->state == EXPAND_SINGLE)
	{
		exp->result[(*exp->position)++] = '$';
		return (D_SKIP);
	}
	if (**ptr == '?')
	{
		build_exit_status(exp, last_exit);
		(*ptr)++;
		return (D_SKIP);
	}
	if (!(ft_isalpha(**ptr) || **ptr == '_'))
	{
		exp->result[(*exp->position)++] = '$';
		return (D_SKIP);
	}
	return (D_EXPAND);
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
				exp->result[(*exp->position)++] = *value++;
			break ;
		}
		env = env->next;
	}
}
