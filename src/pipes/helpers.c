/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:51 by ssin              #+#    #+#             */
/*   Updated: 2025/12/17 13:20:52 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (*src)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '/';
	dest[i + 1] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	i = ft_strlen(dest);
	while (*src)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*join_path(char *dir, char *cmd)
{
	int		len_cmd;
	int		len_dir;
	char	*path;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	path = malloc(sizeof(char) * (len_cmd + len_dir + 2));
	if (!path)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, cmd);
	return (path);
}

char	*check_file(char *infile)
{
	if (access(infile, F_OK) == -1)
		return (infile);
	return (NULL);
}

char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", PATH_LEN) == 0)
			return (envp[i] + PATH_LEN);
		i++;
	}
	return (NULL);
}
