/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:38:43 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/03 17:25:44 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*path;
	int		len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = malloc(len);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, len);
	ft_strlcat(path, "/", len);
	ft_strlcat(path, cmd, len);
	return (path);
}

static char	*free_return(char **cmd, char **env, char *path)
{
	int	i;

	if (cmd)
	{
		i = 0;
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	if (env)
	{
		i = 0;
		while (env[i])
			free(env[i++]);
		free(env);
	}
	return (path);
}


char	*find_dir(char *cmd, char **envp)
{
	int		i;
	char	*full_path;
	char	**split_env;
	char	*path_env;

	i = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);
	split_env = ft_split(path_env, ':');
	if (!split_env)
		return (NULL);
	while (split_env[i])
	{
		full_path = join_path(split_env[i++], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_return(NULL, split_env, full_path));
		free(full_path);
	}
	return (free_return(NULL, split_env, NULL));
}
