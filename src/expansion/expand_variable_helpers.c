/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:46:24 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/28 17:48:52 by lbueno-m         ###   ########.fr       */
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

static void	append_char(const char **ptr, t_expand *exp)
{
	exp->result[*exp->position] = **ptr;
	(*exp->position)++;
	(*ptr)++;
}

static void	append_dollar(t_expand *exp)
{
	exp->result[*exp->position] = '$';
	(*exp->position)++;
}

bool	build_char(const char **ptr, t_expand *exp)
{
	if (update_state(exp->state, **ptr) || **ptr != '$')
	{
		append_char(ptr, exp);
		return (true);
	}
	return (false);
}

static void	build_exit_code(t_expand *exp, int last_exit)
{
	char	*exit_str;
	size_t	j;

	exit_str = ft_itoa(last_exit);
	if (!exit_str)
		return ;
	j = 0;
	while (exit_str[j])
	{
		exp->result[*exp->position] = exit_str[j];
		(*exp->position)++;
		j++;
	}
	free(exit_str);
}

t_dollar_act	build_dollar(const char **ptr, t_expand *exp, int last_exit)
{
	(*ptr)++;
	if (**ptr == '\0')
	{
		append_dollar(exp);
		return (D_STOP);
	}
	if (*exp->state == EXPAND_SINGLE)
	{
		append_dollar(exp);
		return (D_SKIP);
	}
	if (**ptr == '?')
	{
		build_exit_code(exp, last_exit);
		(*ptr)++;
		return (D_SKIP);
	}
	if (!(ft_isalpha(**ptr) || **ptr == '_'))
	{
		append_dollar(exp);
		return (D_SKIP);
	}
	return (D_EXPAND);
}

size_t	read_var_name(const char **ptr)
{
	size_t	var_len;

	var_len = 0;
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '_'))
	{
		(*ptr)++;
		var_len++;
	}
	return (var_len);
}

static void	append_var_value(t_expand *exp, const char *value)
{
	while (*value)
	{
		exp->result[*exp->position] = *value;
		(*exp->position)++;
		value++;
	}
}

void	copy_var_value(const char **ptr, t_expand *exp, t_env *env)
{
	const char	*start;
	size_t		var_len;

	start = *ptr;
	var_len = read_var_name(ptr);
	while (env)
	{
		if (ft_strncmp(env->key, start, var_len) == 0
			&& (env->key)[var_len] == '\0')
		{
			append_var_value(exp, env->value);
			break ;
		}
		env = env->next;
	}
}
