/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:12:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 20:12:27 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_echo(char **argv, int heredoc_fd)
{
	(void)argv;
	(void)heredoc_fd;
	ft_printf("echo: not implemented yet\n");
	return (0);
}
