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

int	error_cd(char *msg)
{
    ft_printf("%s", msg);
	return (1);
}

char	*get_env_value(t_env *internal_envp, char *key)
{
	while (internal_envp)
	{
		if (ft_strcmp(internal_envp->key, key) == 0)
			return (internal_envp->value);
		else
			error_cd("cd: HOME not set\n");
		internal_envp = internal_envp->next;
	}
	return (NULL);
}

void	set_cwd(char **cwd_argv)
{
	char	*cwd;
	cwd = getcwd(NULL, 0);
	cwd_argv[0] = "OLDPWD";
	cwd_argv[1] = cwd;
	cwd_argv[2] = NULL;
}

void	update_oldpwd_env(t_env *internal_envp)
{
	char	*cwd_argv[3];
	int		added_var;

	set_cwd(cwd_argv);
	added_var = builtin_export(cwd_argv, internal_envp);
	if (!added_var)
		error_cd("cd: error adding env var\n");
}

int	builtin_cd(char **argv, t_env *internal_envp)
{
	char	*dir;

	update_oldpwd_env(internal_envp);
	if (argv[2])
		return (error_cd("cd: too many arguments\n"));
	dir = argv[1];
	if (!dir)
		dir = get_env_value(internal_envp, HOME);
	if (chdir(dir) != 0)
		return (error_cd("cd: no such file or directory\n"));
	return (0);
}
