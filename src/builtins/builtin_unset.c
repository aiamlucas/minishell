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

int	search_internal_env(t_env *head, char *argv, t_env **env)
{
	t_env	*node_to_remove;
	t_env	*previous;
	t_env	*tmp;

	tmp = head;
	previous = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, argv))
		{
			node_to_remove = tmp;
			if (tmp == head)
			{
				*env = (*env)->next;
				return (0);
			}
			tmp = tmp->next;
			previous->next = tmp;
			free(node_to_remove);
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
	int		printed_error;
	t_env	*head;

	index = 1;
	printed_error = 0;
	head = *internal_env;
	if (!argv[index])
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (argv[index])
	{
		if (!is_valid_key(argv[index]) && !printed_error)
		{
			ft_printf("unset: %s: invalid parameter name\n", argv[index]);
			printed_error = 1;
		}
		if (!search_internal_env(head, argv[index], internal_env))
			return (0);
		index++;
	}
	return (0);
}
