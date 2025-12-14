/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:52:20 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/14 20:09:53 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*command_new(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->argv = NULL;
	node->redirections = NULL;
	node->next = NULL;
	return (node);
}

t_command	*command_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	command_add_back(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = command_last(*lst);
	last->next = new;
}

void	command_clear(t_command **lst)
{
	t_command	*tmp;
	int			i;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)-> argv[i])
		{
			i = 0;
			while ((*lst)->argv[i])
			{
				free((*lst)->argv[i]);
				i++;
			}
			free((*lst)->argv);
		}
	}
	redir_clear(&(*lst)->redirections);
	free(*lst);
	*lst = tmp;
}
