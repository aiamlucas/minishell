/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:10:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/02 16:17:12 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	error_cd(char *msg)
{
    ft_printf("%s", msg);
	return (1);
}

static char	*get_env_value(char *key, t_env *internal_envp)
{
	while (internal_envp)
	{
		if (ft_strcmp(internal_envp->key, key) == 0)
			return (internal_envp->value);
		// fix this else
		/*else
			error_cd("cd: HOME not set\n");*/
		internal_envp = internal_envp->next;
	}
	return (NULL);
}

static void	pwd_env_manager(char *key, char *value, t_env *internal_envp)
{
	char	*cwd_old_address;
	int		added_var;

	if (!value)
	{
		cwd_old_address = get_env_value("PWD", internal_envp);
		added_var = update_env(key, cwd_old_address, internal_envp);
	}
	else
		added_var = update_env(key, value, internal_envp);
	if (!added_var)
		error_cd("cd: error adding env var\n");
}

int	builtin_cd(char **argv, t_env *internal_envp)
{
	char	*dir;

	pwd_env_manager(OLDPWD, NULL, internal_envp);
	if (argv[2])
		return (error_cd("cd: too many arguments\n"));
	dir = argv[1];
	if (!dir)
		dir = get_env_value(HOME, internal_envp);
	if (chdir(dir) != 0)
		return (error_cd("cd: no such file or directory\n"));
	// check this case with the flow: env -> cd -> env -> cd Documents/core/3/minishell -> env -> check PWD
	pwd_env_manager(PWD, dir, internal_envp);
	return (0);
}
