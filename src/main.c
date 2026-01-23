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

static void	init_data(t_data *data, char **envp)
{
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
