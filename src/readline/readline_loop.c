/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:10:57 by ssin              #+#    #+#             */
/*   Updated: 2026/02/25 19:31:01 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_fd(int *fd)
{
	fd[0] = 0;
	fd[1] = 0;

	if (pipe(fd) == -1)
	{
		ft_printf("heredoc error pipe\n");
		return (0);
	}
	return (1);
}

static int	pre_execution(int fd, t_data *data)
{
	char		buffer[1024];

	ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0) {
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	return (execute_command(data, fd));
}

static char	*join_with_newline(char *line, char *temp)
{
	char	*with_newline;
	char	*joined;

	with_newline = ft_strjoin(line, "\n");
	if (!with_newline)
		return (NULL);
	joined = ft_strjoin(with_newline, temp);
	free(with_newline);
	return (joined);
}

static char	*read_continuation_line(char *current_line)
{
	char	*temp;
	char	*result;

	temp = readline("> ");
	if (!temp)
		return (NULL);
	if (check_signal())
	{
		free(temp);
		return (NULL);
	}
	result = join_with_newline(current_line, temp);
	free(temp);
	return (result);
}

static char	*readline_with_continuation(const char *input)
{
	char	*line;
	char	*new_line;

	line = readline(input);
	if (!line)
		return (NULL);
	while (has_unclosed_quotes(line))
	{
		if (check_signal())
		{
			free(line);
			return (NULL);
		}
		new_line = read_continuation_line(line);
		free(line);
		if (!new_line)
			return (NULL);
		line = new_line;
	}
	return (line);
}

static int	process_input(char *input, t_data *data)
{
	int	fd[2];
	int	exit_code;

	fd[0] = 0;
	fd[1] = 0;
	exit_code = 0;
	data->tokens = lexer(input);
	//printf("tokens\n");
	//print_tokens(data->tokens);
	//printf("\n after expansion: \n");
	expand_tokens(data->tokens, data->internal_env, data->last_exit);
	// print_tokens(data->tokens);
	// printf("\n after quote removal: \n");
	remove_quotes(data->tokens);
	// print_tokens(data->tokens);
	data->commands = parser(data->tokens);
	// print_commands(data->commands); // for debugging
	token_clear(&data->tokens);
	exit_code = handle_heredoc(data, fd);
	if (exit_code == 0)
	{
		if (fd[0] > 0)
		{
			exit_code = pre_execution(fd[0], data);
			close(fd[0]);
		}
		else
			exit_code = execute_command(data, 0);
	}
	else
	{
		if (fd[0] > 0)
			close(fd[0]);
		if (fd[1] > 0)
			close(fd[1]);
	}
	command_clear(&data->commands);
	if (check_signal())
		exit_code = get_signal_exit_code();
	return (exit_code);
}

static int	check_input_validation(char *input)
{
	if (check_signal())
	{
		if (input)
			free(input);
		reset_signal();
		return (1);
	}
	if (!input)
		return (-1);
	if (is_empty_input(input))
	{
		free(input);
		return (1);
	}
	return (0);
}

static bool	handle_input_line(char *input, t_data *data)
{
	int	validation;
	int	exit_code;

	validation = check_input_validation(input);
	if (validation == -1)
	{
		ft_printf("exit\n");
		return (false);
	}
	if (validation == 1)
		return (true);
	add_history(input);
	exit_code = process_input(input, data);
	data->last_exit = exit_code;
	free(input);
	return (true);
}

void	readline_loop(t_data *data)
{
	char		*input;

	while (1)
	{
		reset_signal();
		input = readline_with_continuation("$[ 🛸 ]>");
		if (!handle_input_line(input, data))
			break ;
	}
}
