/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:46:37 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/09 15:05:55 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(char **argv)
{
	ft_printf("exit\n");
	if (!argv[1])
		exit(0);
	if (!is_numeric(argv[1]))
	{
		ft_printf("exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	exit((unsigned char)ft_atoi(argv[1]));
}
