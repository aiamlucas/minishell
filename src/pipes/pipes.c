/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:45 by ssin              #+#    #+#             */
/*   Updated: 2025/12/17 13:20:47 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	child1(int *fd, char *file, char *cmd1, t_args params)
{
	int		infile;
	char	**split_cmd;

	infile = open(file, O_RDONLY);
	if (infile == -1)
	{
		free(*params.arg);
		error_handler("Failed open infile");
	}
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[1]);
	split_cmd = ft_split(cmd1, ' ');
	if (*params.arg)
		execve(*params.arg, split_cmd, params.envp);
	free(*params.arg);
	free_memo(split_cmd);
	error_handler("Failed execve1");
}

static void	child2(int *fd, char *file, char *cmd2, t_args params)
{
	int		outfile;
	char	**split_cmd;

	outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		free(*params.arg);
		error_handler("Failed open outfile");
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(outfile);
	split_cmd = ft_split(cmd2, ' ');
	if (*params.arg)
		execve(*params.arg, split_cmd, params.envp);
	free(*params.arg);
	free_memo(split_cmd);
	error_handler("Failed execve2");
}

static char	*find_dir(char *cmd, char **envp)
{
	int		i;
	char	*full_path;
	char	**split_cmd;
	char	**split_env;
	char	*path_env;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);
	split_env = ft_split(path_env, ':');
	split_cmd = ft_split(cmd, ' ');
	while (split_env[i])
	{
		full_path = join_path(split_env[i], split_cmd[0]);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_return(split_cmd, split_env, full_path));
		free(full_path);
		i++;
	}
	return (free_return(split_cmd, split_env, NULL));
}

static void	pipes(t_args ept, int pid1, int pid2, int *fd)
{
	char	*dir1;
	char	*dir2;
	t_args	params;

	dir1 = find_dir(ept.arg[1], ept.envp);
	dir2 = find_dir(ept.arg[2], ept.envp);
	params.arg = &dir1;
	params.envp = ept.envp;
	if (!dir1 || !dir2 || access(dir1, F_OK) != 0 || access(dir2, F_OK) != 0)
		free_dir(&dir1, &dir2, "Invalid command");
	pid1 = fork();
	if (pid1 == -1)
		free_dir(&dir1, &dir2, "Failed fork1");
	if (pid1 == 0)
		child1(fd, ept.arg[0], ept.arg[1], params);
	pid2 = fork();
	free(dir1);
	params.arg = &dir2;
	if (pid2 == -1)
		free_dir(&dir1, &dir2, "Failed fork2");
	if (pid2 == 0)
		child2(fd, ept.arg[3], ept.arg[2], params);
	free(dir2);
}

int	create_pipe(int argc, char **argv, char **envp)
{
	int		pid1;
	int		pid2;
	int		fd[2];
	char	*inv_file;
	t_args	entrypoint;

	if (argc != 5)
		error_handler("Argument is missing");
	inv_file = check_file(argv[1]);
	if (inv_file)
		error_handler("Check arguments (infile or outfile)");
	entrypoint.arg = &argv[1];
	entrypoint.envp = envp;
	pid1 = 0;
	pid2 = 0;
	if (pipe(fd) == -1) error_handler("Failed to create a pipe");
	pipes(entrypoint, pid1, pid2, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
