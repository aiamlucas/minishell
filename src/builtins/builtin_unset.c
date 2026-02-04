/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:37 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 21:43:07 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(char **argv, t_env **internal_envp)
{
	int		index;
	int		printed_error;
	t_env	*tmp;
	t_env	*head;
	t_env	*previous;
	t_env	*node_to_remove;

	index = 1;
	printed_error = 0;
	head = *internal_envp;
	previous = NULL;
	// check if the node is the head of internal_envp
	// this way just removing the head and pointing to the second node will work
	if (!argv[index])
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	while (argv[index])
	{
		tmp = head;
		if (!is_valid_key(argv[index]) && !printed_error)
		{
			ft_printf("unset: %s: invalid parameter name\n", argv[index]);
			printed_error = 1;
		}
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, argv[index]))
			{
				node_to_remove = tmp;
				if (tmp == head)
				{
					*internal_envp = (*internal_envp)->next;
					return (0);
				}
				tmp = tmp->next;
				previous->next = tmp;
				// free_list(node_to_remove);
				break ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
		index++;
	}
	return (0);
}
