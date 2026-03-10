/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_copy_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:55:38 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/06 12:31:55 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	build_exit_code(t_expand *exp, int last_exit)
{
	char	*exit_str;
	size_t	i;

	exit_str = ft_itoa(last_exit);
	if (!exit_str)
		return ;
	i = 0;
	while (exit_str[i])
	{
		exp->result[*exp->position] = exit_str[i];
		(*exp->position)++;
		i++;
	}
	free(exit_str);
}

size_t	advance_and_count_name(const char **ptr)
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

void	append_var_value(t_expand *exp, const char *value)
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
	var_len = advance_and_count_name(ptr);
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
