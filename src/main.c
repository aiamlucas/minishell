/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:06:26 by ssin              #+#    #+#             */
/*   Updated: 2026/02/26 09:41:18 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_data(t_data *data, char **envp)
{
	t_env	*list;

	list = NULL;
	create_env_list(&list, envp);
	// print_env_list(list);
	data->envp = envp;
	data->internal_env = list;
	data->tokens = NULL;
	data->commands = NULL;
	data->last_exit = 0;
}

void	cleanup_data(t_data *data)
{
	command_clear(&data->commands);
	token_clear(&data->tokens);
	free_env_list(&data->internal_env);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1)
	{
		ft_printf("minishell: no arguments accepted\n");
		return (1);
	}
	(void)argv;
	init_data(&data, envp);
	setup_signals();
	readline_loop(&data);
	cleanup_data(&data);
	return (0);
}
