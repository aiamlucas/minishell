/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/21 13:39:38 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_argv(char **argv)
{
	if (!*argv)
		return (0);
	else
	{
		if (argv[1] && (ft_isalpha(argv[1][0]) || argv[1][0] == '_'))
			return (1);
		return (0);
	}
}

// this function should go in handle_errors.c (?)
int	print_invalid(char *msg)
{
	ft_printf("%s", msg);
	return (1);
}

void	create_env(char *key, char *value, t_env *internal_env)
{
	// ft_isalpha(key[i]), ft_isdigit(key[i]), key[i] == '_' // check key requirements
		// invalid key error
	// node = new_env_node(key, value);
	// list_add_back(internal_env, node);
}

void	update_env(char *key, char *value, t_env *internal_env)
{
	t_env	*tmp;

	tmp = internal_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
			tmp->value=value;
		tmp = tmp->next;
	}
	ft_printf("valid k: %s v: %s\n", key, value);
}

int	key_exists(char *key, t_env *internal_env)
{
	t_env	*tmp;

	tmp = internal_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_export(char **argv, t_env *internal_env)
{
	char	*key;
	char	*value;
	int		arg_valid;

	key = NULL;
	value = NULL;
	arg_valid = is_valid_argv(argv);
	if (arg_valid)
	{
		value = ft_strchr(argv[1], '=');
		if (value)
		{
			key = ft_substr(argv[1], 0, value - argv[1]);
			value++;
		}
		else
		{
			key = ft_strdup(argv[1]);
			//	handle variables without value
		}
		if (key_exists(key))
		{
			// if (ft_strcmp(argv[0], "OLDPWD") && argv[1])
				// update OLDPWD and PWD
			update_env(key, value, internal_env);
		}
		else
			create_env(key, value, internal_env);
	}
	else
		return (print_invalid("export: invalid argument\n"));
	return (0);
}
