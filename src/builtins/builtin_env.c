/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:12:33 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/13 16:15:23 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_env(t_env *envp)
{
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

//int	builtin_env(t_env *envp)
//{
//	handle variables without value
//	while (envp)
//	{
//		if (envp->value)
//			ft_printf("%s=%s\n", envp->key, envp->value);
//		envp = envp->next;
//	}
//	return (0);
//}
