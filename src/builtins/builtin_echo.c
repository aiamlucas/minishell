/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:12:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/24 19:05:30 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_flag(char **argv, int *i, int *newline)
{
	int	j;

	j = 2;
	while (argv)
	{
		if (argv[*i][0] == '-' && argv[*i][1] == 'n')
		{
			j = 2;
			while (argv[*i][j] == 'n')
				j++;
			if (argv[*i][j] == '\0')
			{
				*newline = 0;
				(*i)++;
				continue ;
			}
		}
		break ;
	}
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!argv[i] || (argv[i][0] == '"' && argv[i][1] == '"'
		&& argv[i][2] == '\0'))
	{
		ft_printf("\n");
		return (0);
	}
	check_flag(argv, &i, &newline);
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
