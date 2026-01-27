/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:38:43 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/13 19:01:43 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_path(t_env *envp)
{
	t_env	*current;

	current = envp;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (current->value);
		current = current->next;
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

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*cleanup_and_return(char **split_env, char *path)
{
	free_split(split_env);
	return (path);
}

char	*find_dir(char *cmd, t_env *envp)
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
			return (cleanup_and_return(split_env, full_path));
		free(full_path);
	}
	return (cleanup_and_return(split_env, NULL));
}
