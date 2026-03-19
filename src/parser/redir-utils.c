/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:52:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/17 10:23:27 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*redir_new(t_token_type type, char *file, bool should_expand)
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
	node->should_expand = should_expand;
	node->fd = -1;
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
		if ((*lst)->type == TOKEN_HEREDOC && (*lst)->fd != -1)
			close((*lst)->fd);
		free((*lst)->target);
		free(*lst);
		*lst = tmp;
	}
}

t_redir	*create_heredoc_redir(t_token *target)
{
	bool	should_expand;
	char	*delimiter;
	t_redir	*redir;

	should_expand = true;
	delimiter = target->value;
	while (*delimiter)
	{
		if (*delimiter == C_S_QUOTE || *delimiter == C_D_QUOTE)
		{
			should_expand = false;
			break ;
		}
		delimiter++;
	}
	delimiter = remove_quote_chars(target->value);
	redir = redir_new(TOKEN_HEREDOC, delimiter, should_expand);
	free(delimiter);
	return (redir);
}
