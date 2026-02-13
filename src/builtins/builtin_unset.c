/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:37 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/09 15:44:36 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	clean_node(t_env **internal_env, t_env *node_to_remove)
{
	*internal_env = (*internal_env)->next;
	free_env_node(node_to_remove);
	return (0);
}

int	search_internal_env(t_env *head, char *argv, t_env **internal_env)
{
	t_env	*tmp;
	t_env	*previous;
	t_env	*node_to_remove;

	tmp = head;
	previous = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, argv))
		{
			node_to_remove = tmp;
			if (tmp == head)
				return (clean_node(internal_env, node_to_remove));
			tmp = tmp->next;
			previous->next = tmp;
			free_env_node(node_to_remove);
			break ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	builtin_unset(char **argv, t_env **internal_env)
{
	int		index;
	int		exit_code;
	t_env	*head;

	index = 1;
	exit_code = 0;
	head = *internal_env;
	if (!argv[index])
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (argv[index])
	{
		if (!is_valid_key(argv[index]) && !exit_code)
		{
			ft_printf("unset: %s: invalid parameter name\n", argv[index]);
			exit_code = 1;
		}
		if (!search_internal_env(head, argv[index], internal_env))
			exit_code = 1;
		index++;
	}
	return (exit_code);
}
