/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:12:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/14 11:03:19 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_echo(char **argv)
{
    int i = 1;
    int newline = 1;

    if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
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
