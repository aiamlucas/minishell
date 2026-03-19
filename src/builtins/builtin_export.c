/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/19 11:58:43 by lbueno-m         ###   ########.fr       */
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

int	print_env(t_env *internal_env)
{
	t_env	*tmp;

	tmp = internal_env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s=\"\"\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_export(char **argv, t_env **intrnl_env)
{
	int	index;
	int	exit_code;

	index = 0;
	exit_code = 0;
	if (!argv[1])
		return (print_env(*intrnl_env));
	while (argv[++index])
		process_export_arg(argv, index, intrnl_env, &exit_code);
	return (exit_code);
}
