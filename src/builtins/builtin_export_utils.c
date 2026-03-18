/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:14:13 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/18 20:35:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_key_value(char **argv, char **key, char **value, int index)
{
	char	*equals_pos;

	equals_pos = ft_strchr(argv[index], '=');
	if (equals_pos)
	{
		*key = ft_substr(argv[index], 0, equals_pos - argv[index]);
		*value = equals_pos + 1;
	}
}

static void	clear_data(char **key, char **value)
{
	if (*key)
		free(*key);
	*key = NULL;
	*value = NULL;
}

void	process_export_arg(char **argv, int index, t_env **intrnl_env,
				int *exit_code)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (is_valid_key(argv[index]))
	{
		get_key_value(argv, &key, &value, index);
		if (key)
			set_env(check_key(key, *intrnl_env), key, value, intrnl_env);
		clear_data(&key, &value);
	}
	else
		*exit_code = 1;
}
