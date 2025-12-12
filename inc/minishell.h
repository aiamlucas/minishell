#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "minishell_macros.h"

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct	s_token	*next;
}	t_token;

// Redirecion struct to be placed inside the commands list
typedef struct	s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_command
{
	char				**argv;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

typedef struct	s_data
{
	char		**envp;
	t_token		*tokens;
	t_command	*commands;
	int			last_exit;
}	t_data;

t_token	*new_token(char *value, t_token_type type);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *new);
void	token_clear(t_token **lst);
t_token	*lexer(char *line);
void	readline_loop();

#endif
