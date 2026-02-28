/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_copy_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:55:38 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/28 18:01:54 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	build_exit_code(t_expand *exp, int last_exit)
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
