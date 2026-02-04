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

int	is_valid_key(char *name)
{
	size_t	i;

	if (!*name || ft_strlen(name) == 0)
		return (0);

	i = 0;

	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);

	while (i < ft_strlen(name) && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			ft_printf("export: not valid in this context: %s\n", name);
			return (0);
		}
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
	int		index;

	key = NULL;
	value = NULL;
	index = 1;
	while (argv[index])
	{
		arg_valid = is_valid_key(argv[index]);
		if (arg_valid)
		{
			equals_pos = ft_strchr(argv[index], '=');
			if (equals_pos)
			{
				key = ft_substr(argv[index], 0, equals_pos - argv[index]);
				value = equals_pos + 1;
			}
			else
			{
				key = ft_strdup(argv[index]);
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
			ft_printf("export: invalid argument\n");
		index++;
	}
	return (0);
}
