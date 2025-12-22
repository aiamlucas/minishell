/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:39 by ssin              #+#    #+#             */
/*   Updated: 2025/12/17 13:20:41 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define PATH_LEN	5

typedef struct s_args {
	char	**arg;
	char	**envp;
}	t_args;

// Pipe process functions
int		create_pipe(int argc, char **argv, char **envp);

// String helpers
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*join_path(char *dir, char *cmd);
char	*check_file(char *infile);
char	*get_env_path(char **envp);

// Error handling
void	error_handler(char *msg);
void	free_dir(char **dir1, char **dir2, char *msg);
void	free_memo(char **memo);
char	*free_return(char **cmd, char **env, char *path);

#endif
