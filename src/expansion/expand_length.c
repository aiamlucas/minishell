/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:24:52 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/24 09:18:52 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	handle_char(const char **ptr, size_t *len, t_expand_state *state)
{
	if (update_state(state, **ptr) || **ptr != '$')
	{
		(*len)++;
		(*ptr)++;
		return (true);
	}
	return (false);
}

static void	add_exit_len(size_t *len, int last_exit)
{
	char	*exit_str;

	exit_str = ft_itoa(last_exit);
	if (!exit_str)
		return ;
	(*len) += ft_strlen(exit_str);
	free(exit_str);
}

static t_dollar_act	handle_dollar(const char **ptr, size_t *len,
									t_expand_state state, int last_exit)
{
	(*ptr)++;
	if (**ptr == '\0')
	{
		(*len)++;
		return (D_STOP);
	}
	if (state == EXPAND_SINGLE)
	{
		(*len)++;
		return (D_SKIP);
	}
	if (**ptr == '?')
	{
		add_exit_len(len, last_exit);
		(*ptr)++;
		return (D_SKIP);
	}
	if (!(ft_isalpha(**ptr) || **ptr == '_'))
	{
		(*len)++;
		return (D_SKIP);
	}
	return (D_EXPAND);
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
	size_t			len;
	const char		*ptr;
	t_expand_state	state;
	t_dollar_act	action;

	ptr = str;
	len = 0;
	state = EXPAND_NORMAL;
	while (*ptr)
	{
		if (handle_char(&ptr, &len, &state))
			continue ;
		action = handle_dollar(&ptr, &len, state, last_exit);
		if (action == D_STOP)
			break ;
		if (action == D_SKIP)
			continue ;
		len += find_var_len(&ptr, internal_env);
	}
	return (len);
}
