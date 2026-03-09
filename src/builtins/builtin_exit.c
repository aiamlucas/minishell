/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:46:37 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/25 10:13:10 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_numeric(char *str)
{
	if (!*str)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(char **argv, t_data *data)
{
	int	exit_code;

	ft_printf("exit\n");
	if (!argv[1])
	{
		cleanup_data(data);
		exit(0);
	}
	if (!is_numeric(argv[1]) || !ft_safe_atoi(argv[1], &exit_code))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		cleanup_data(data);
		exit(2);
	}
	if (argv[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	cleanup_data(data);
	exit((unsigned char)exit_code);
}
