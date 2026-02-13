/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/13 10:32:22 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	create_env(char *key, char *value, t_env **internal_env)
{
	char	*content;
	char	*tmp;
	t_env	*node;

	tmp = ft_strjoin(key, "=");
	content = ft_strjoin(tmp, value);
	node = new_env_node(content);
	list_add_back(internal_env, node);
	free(tmp);
	free(content);
}

void	set_env(int key_exists, char *key, char *value, t_env **internal_env)
{
	if (key_exists)
		update_env(key, value, *internal_env);
	else
		create_env(key, value, internal_env);
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

int	print_env(t_env *internal_env)
{
	t_env	*tmp;

	tmp = internal_env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			ft_printf("declare -x %s=\"\"\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_export(char **argv, t_env **intrnl_env)
{
	char	*key;
	char	*value;
	int		index;
	int		exit_code;

	key = NULL;
	value = NULL;
	index = 0;
	exit_code = 0;
	if (!argv[1])
		return (print_env(*intrnl_env));
	while (argv[++index])
	{
		if (is_valid_key(argv[index]))
		{
			get_key_value(argv, &key, &value, index);
			if (key)
				set_env(check_key(key, *intrnl_env), key, value, intrnl_env);
			clear_data(&key, &value);
		}
		else
		{
			ft_printf("export: invalid argument\n");
			exit_code = 1;
		}
	}
	return (exit_code);
}
