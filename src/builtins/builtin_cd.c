/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:10:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/11 11:15:44 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	error_cd(char *msg)
{
	ft_printf("%s\n", msg);
	return (1);
}

static char	*get_env_value(char *key, t_env *internal_envp)
{
	while (key && internal_envp)
	{
		if (ft_strcmp(internal_envp->key, key) == 0)
			return (internal_envp->value);
		internal_envp = internal_envp->next;
	}
	return (NULL);
}

static void	pwd_env_manager(char *key, char *value, t_env *internal_envp)
{
	char	*cwd_old_address;

	if (ft_strcmp(key, OLDPWD) == 0)
	{
		cwd_old_address = get_env_value(PWD, internal_envp);
		update_env(key, cwd_old_address, internal_envp);
	}
	else
		update_env(key, value, internal_envp);
}

int	builtin_cd(char **argv, t_env *internal_envp)
{
	char	*dir;
	char    cwd[PATH_MAX];

	pwd_env_manager(OLDPWD, NULL, internal_envp);
	if (argv[1] && argv[2])
		return (error_cd("cd: too many arguments"));
	dir = argv[1];
	if (!dir)
	{
		dir = get_env_value(HOME, internal_envp);
		if (!dir)
			return (error_cd("minishell: cd: HOME not set"));
	}
	if (chdir(dir) != 0)
		return (error_cd("cd: no such file or directory"));
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (error_cd("cd: error retrieving current directory\n"));
	pwd_env_manager(PWD, cwd, internal_envp);
	return (0);
}
