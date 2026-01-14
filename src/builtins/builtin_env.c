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

int	builtin_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

/*int	builtin_unset(char **envp)
{
	//unsetenv(envp);
}

char	*builtin_export(char **envp, char *value)
{
	// setenv(const char *envp, const char *value, int overwrite);
}*/
