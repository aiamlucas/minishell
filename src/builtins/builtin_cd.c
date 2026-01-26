/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:10:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/04 20:10:43 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(t_env *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	builtin_cd(char **argv, t_env *envp)
{
	(void)envp;
	char	*dir;

	dir = argv[1];
	if (!dir)
		dir = getenv(HOME); // get_env_value(envp, HOME);
	if (chdir(dir) != 0)
	{
		ft_printf("cd: no such file or directory");
		return (1);
	}
	return (0);
}