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

void	create_env_list(t_list **list, char **envp)
{
	t_list	*node;

	while (*envp)
	{
		node = ft_lstnew(*envp);
		ft_lstadd_back(list, node);
		envp++;
	}
}

static void	init_data(t_data *data, char **envp)
{
	t_list	*list = NULL;
	create_env_list(&list, envp);
	//print_env_list(list);
	data->envp = envp;
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
