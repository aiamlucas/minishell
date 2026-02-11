/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:52:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/11 10:58:53 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*redir_new(t_token_type type, char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->target = ft_strdup(file);
	if (!node->target)
	{
		free(node);
		return (NULL);
	}
	node->type = type;
	node->next = NULL;
	return (node);
}

t_redir	*redir_last(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = redir_last(*lst);
	last->next = new;
}

void	redir_clear(t_redir **lst)
{
	t_redir	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->target);
		free(*lst);
		*lst = tmp;
	}
}
