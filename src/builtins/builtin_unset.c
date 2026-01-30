/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:37 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 21:43:07 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(char **argv, t_env *envp)
{
	(void)envp;
	(void)argv;
	ft_printf("unset: not implemented yet\n");
	return (0);
}
