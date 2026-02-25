/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:47:55 by ssin              #+#    #+#             */
/*   Updated: 2026/02/25 10:08:19 by lbueno-m         ###   ########.fr       */
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

// new env node logic without ft_split
t_env	*new_env_node(void *content)
{
	t_env	*node;
	char	*separator;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	separator = ft_strchr(content, '=');
	if (!separator)
	{
		free(node);
		return (NULL);
	}
	node->key = ft_substr(content, 0, separator - (char *)content);
	node->value = ft_strdup(separator + 1);
	node->next = NULL;
	return (node);
}

// for cleaning all the env list 
void	free_env_list(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free_env_node(*lst);
		*lst = temp;
	}
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
