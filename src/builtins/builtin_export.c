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

static int	is_valid_key(char **argv)
{
	char	*name;
	size_t	i;

	if (!*argv || !argv[1])
		return (0);
	name = argv[1];
	
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	
	if (i == 0)
		return (0);
		
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
		
	i = 1;
	while (i < ft_strlen(name) && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

// this function should go in handle_errors.c (?)
int	print_invalid(char *msg)
{
	ft_printf("%s", msg);
	return (1);
}

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

int	update_env(char *key, char *value, t_env *internal_env)
{
	t_env	*tmp;
	char	*cp_value;

	if (value)
		cp_value = ft_strdup(value);
	else
		cp_value = NULL;
	tmp = internal_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = cp_value;
			return (1);
		}
		tmp = tmp->next;
	}
	ft_printf("valid k: %s v: %s\n", key, value);
	if (cp_value)
		free(cp_value);
	return (0);
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

int	builtin_export(char **argv, t_env *internal_env)
{
	char	*key;
	char	*value;
	char	*equals_pos;
	int		arg_valid;

	key = NULL;
	value = NULL;
	arg_valid = is_valid_key(argv);
	if (arg_valid)
	{
		equals_pos = ft_strchr(argv[1], '=');
		if (equals_pos)
		{
			key = ft_substr(argv[1], 0, equals_pos - argv[1]);
			value = equals_pos + 1;
		}
		else
		{
			key = ft_strdup(argv[1]);
			value = NULL;
		}
		if (key_already_exists(key, internal_env))
		{
			if (equals_pos)
				update_env(key, value, internal_env);
		}
		else
		{
			if (equals_pos)
				create_env(key, value, internal_env);
		}
		free(key);
	}
	else
		return (print_invalid("export: invalid argument\n"));
	return (0);
}
