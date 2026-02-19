/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:47:55 by ssin              #+#    #+#             */
/*   Updated: 2026/01/27 18:47:56 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*list_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	list_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = list_last(*lst);
	last->next = new;
}

t_env	*new_env_node(void *content)
{
	t_env	*node;
	char	**split;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	split = ft_split(content, '=');
	if (!split)
	{
		free(node);
		return (NULL);
	}
	node->key = split[0];
	node->value = split[1];
	node->next = NULL;
	free(split);
	return (node);
}

void	create_env_list(t_env **list, char **envp)
{
	t_env	*node;

	while (*envp)
	{
		node = new_env_node(*envp);
		if (node)
			list_add_back(list, node);
		envp++;
	}
}
