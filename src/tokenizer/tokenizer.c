#include "../inc/minishell.h"

t_token	*lexer(char *line)
{
	t_token	*tokens = NULL;
	char	*start;
	int		len;
	char	*word;

	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		if (*line == '|')
		{
			token_add_back(&tokens, new_token("|", TOKEN_PIPE));
			line++;
		}
		else if (*line == '<' && *(line + 1) == '<')
		{
			token_add_back(&tokens, new_token("<<", TOKEN_HEREDOC));
			line +=2;
		}
		else if (*line == '<')
		{
			token_add_back(&tokens, new_token("<", TOKEN_REDIR_IN));
			line++;
		}
		else if (*line == '>' && *(line + 1) == '>')
		{
			token_add_back(&tokens, new_token(">>", TOKEN_REDIR_APPEND));
			line +=2;
		}
		else if (*line == '>')
		{
			token_add_back(&tokens, new_token(">", TOKEN_REDIR_OUT));
			line++;
		}
		else
		{
			start = line;
			while (*line && !ft_isspace(*line) && *line != '|' && *line != '<' && *line != '>')
				line++;
			len = line - start;
			word = ft_substr(start, 0, len);
			token_add_back(&tokens, new_token(word, TOKEN_WORD));
			free(word);
		}
	}
	return (tokens);
}
