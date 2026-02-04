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
			//ft_printf("unset: not valid in this context: %s\n", name);
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_unset(char **argv, t_env *internal_envp)
{
	(void)argv;
	(void)internal_envp;
	int		index;
	int		printed_error;
	t_env	*tmp;
	t_env	*head;
	t_env	*previous;
	t_env	*current;

	index = 1;
	printed_error = 0;
	head = internal_envp;
	tmp = internal_envp;
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
		if (!is_valid_key(argv[index]) && !printed_error)
		{
			ft_printf("unset: %s: invalid parameter name\n", argv[index]);
			printed_error = 1;
		}
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, argv[index]))
			{
				current = tmp;
				tmp = tmp->next;
				previous->next = tmp;
				// free_list(current);
				break ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
		index++;
		tmp = head;
	}
	return (0);
}
