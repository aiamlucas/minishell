/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/02 19:09:48 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	create_env(char *key, char *value, t_env *internal_env)
{
	char	*content;
	t_env	*node;

	content = ft_strjoin(key, "=");
	content = ft_strjoin(content, value);
	node = new_env_node(content);
	list_add_back(&internal_env, node);
	free(content);
}

static int	key_already_exists(char *key, t_env *internal_env)
{
	t_env	*tmp;

	tmp = internal_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	clear_data(char **key, char **value)
{
	if (*key)
		free(*key);
	*key = NULL;
	*value = NULL;
}

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

int	builtin_export(char **argv, t_env *internal_env)
{
	char	*key;
	char	*value;
	int		arg_valid;
	int		index;

	index = 1;
	while (argv[index])
	{
		arg_valid = is_valid_key(argv[index]);
		if (arg_valid)
		{
			get_key_value(argv, &key, &value, index);
			if (key && key_already_exists(key, internal_env))
				update_env(key, value, internal_env);
			else
				create_env(key, value, internal_env);
			clear_data(&key, &value);
		}
		else
			ft_printf("export: invalid argument\n");
		index++;
	}
	return (0);
}
