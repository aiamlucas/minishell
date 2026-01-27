/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:06:26 by ssin              #+#    #+#             */
/*   Updated: 2026/01/23 15:28:09 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_last(*lst);
	last->next = new;
}

t_env	*ft_new(void *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = content;
	node->next = NULL;
	return (node);
}

void	create_env_list(t_env **list, char **envp)
{
	t_env	*node;

	while (*envp)
	{
		node = ft_new(*envp);
		ft_add_back(list, node);
		envp++;
	}
}

static void	init_data(t_data *data, char **envp)
{
	t_env	*list = NULL;
	create_env_list(&list, envp);
	print_env_list(list);
	data->envp = envp;
	data->internal_env = list;
	data->tokens = NULL;
	data->commands = NULL;
	data->last_exit = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	(void)argc;
	(void)argv;
	init_data(&data, envp);
	setup_signals();
	readline_loop(&data);
	return (0);
}
