/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:31:00 by ssin              #+#    #+#             */
/*   Updated: 2026/01/25 16:50:35 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define HOME "HOME"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "minishell_macros.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>

extern volatile	sig_atomic_t	g_signal_received;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Redirecion struct to be placed inside the commands list
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char		**envp;
	t_env		*internal_env;
	t_token		*tokens;
	t_command	*commands;
	int			last_exit;
}	t_data;

typedef struct s_child_data
{
	t_command	*cmd;
	int			**pipes;
	int			cmd_index;
	int			total;
	char		**envp;
}	t_child_data;

// maybe we can later have several header files for each part of the project
// until there I make a provisory comment for each part of the project

// core
void		readline_loop(t_data *data);

// lexer
t_token		*new_token(char *value, t_token_type type);
t_token		*token_last(t_token *lst);
void		token_add_back(t_token **lst, t_token *new);
void		token_clear(t_token **lst);
t_token		*lexer(char *line);

// parser

t_command	*command_new(void);
t_command	*command_last(t_command *lst);
void		command_add_back(t_command **lst, t_command *new);
void		command_clear(t_command **lst);
t_redir		*redir_new(t_token_type type, char *file);
t_redir		*redir_last(t_redir *lst);
void		redir_add_back(t_redir **lst, t_redir *new);
void		redir_clear(t_redir **lst);
t_command	*parser(t_token *tokens);
void		create_env_list(t_env **list, char **envp);

// debug
void		print_tokens(t_token *tokens);
void		print_redirections(t_redir *redirections);
void		print_commands(t_command *commands);
void		print_env_list(t_env *list);

// pipeline helpers

int			count_pipeline_commands(t_command *cmd);
void		free_pipes(int **pipes, int count);
void		close_pipes(int **pipes, int count);
int			**create_pipes(int count);

// execution
bool		is_builtin(t_command *cmd);
int			execute_single_command(t_command *cmd, char **envp,
				t_env *internal_env);
int			execute_command(t_data *data);
int			execute_pipeline(t_command *cmds, char **envp);
int			execute_builtin(t_command *cmd, t_env *internal_env);
char		*find_dir(char *cmd, t_env *internal_env);
void		apply_redirections(t_redir *redirections);
void		setup_pipes(int **pipes, int i, int total);
void		child_process(t_child_data *data);
pid_t		fork_child(t_child_data *data);
bool		must_run_in_parent(t_command *cmd);
void		execute_child_command(t_command *cmd, char **envp,
				t_env *internal_env);

// builtins
int			builtin_cd(char **argv, t_env *envp);
int			builtin_echo(char **argv);
int			builtin_env(t_env *internal_env);
int			builtin_export(char **argv, t_env *internal_env);
int			builtin_pwd(void);
int			builtin_unset(char **argv, t_env *internal_env);
int			builtin_exit(char **argv);

// signals

void		setup_signals(void);
void		reset_signals(void);
void		handle_sigint(int sig);
bool		check_signal(void);
void		reset_signal(void);
int			get_signal_exit_code(void);
bool		handle_signal_interrupt(void);

#endif
