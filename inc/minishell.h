/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:31:00 by ssin              #+#    #+#             */
/*   Updated: 2025/12/22 16:08:24 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "minishell_macros.h"
# include <stdbool.h>
# include "pipes.h"

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
	t_token		*tokens;
	t_command	*commands;
	int			last_exit;
}	t_data;

// maybe we can later have several header files for each part of the project
// until there I make a provisory comment for each part of the project

// core
void		readline_loop(char **envp);

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

// debug
void		print_tokens(t_token *tokens);
void		print_redirections(t_redir *redirections);
void		print_commands(t_command *commands);

// execution

char	*get_input_file(t_redir *redirections);
char	*get_output_file(t_redir *redirections);


#endif
