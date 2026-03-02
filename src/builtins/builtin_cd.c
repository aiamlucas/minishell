/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:10:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/02/19 15:37:01 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_value(char *key, t_env *internal_env)
{
	while (key && internal_env)
	{
		if (ft_strcmp(internal_env->key, key) == 0)
			return (internal_env->value);
		internal_env = internal_env->next;
	}
	return (NULL);
}

static void	pwd_env_manager(char *key, char *value, t_env **internal_env)
{
	char	*cwd_old_address;
	int		key_exists;

	key_exists = check_key(key, *internal_env);
	if (ft_strcmp(key, OLDPWD) == 0)
	{
		cwd_old_address = get_env_value(PWD, *internal_env);
		set_env(key_exists, key, cwd_old_address, internal_env);
	}
	else
		set_env(key_exists, key, value, internal_env);
}

int	builtin_cd(char **argv, t_env **internal_env)
{
	char	*dir;
	char	cwd[PATH_MAX];

	pwd_env_manager(OLDPWD, NULL, internal_env);
	if (argv[1] && argv[2])
		return (error_msg("minishell: cd: too many arguments"));
	dir = argv[1];
	if (!dir)
	{
		dir = get_env_value(HOME, *internal_env);
		if (!dir)
			return (error_msg("minishell: cd: HOME not set"));
	}
	if (chdir(dir) != 0)
		return (error_msg("minishell: cd: no such file or directory"));
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (error_msg("minishell: cd: error retrieving current directory\n"));
	pwd_env_manager(PWD, cwd, internal_env);
	return (0);
}
