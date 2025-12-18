/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:06:50 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/18 15:40:29 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

/*
** Test: "echo hello"
** Expected: [echo]->[hello]->NULL
*/
static void	test_simple_command(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "echo hello";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 2)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Simple command", passed);
}

/*
** Test: "cat | grep"
** Expected: [cat]->[|]->[grep]->NULL
*/
static void	test_pipe(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "cat | grep";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 3)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Pipe operator", passed);
}

/*
** Test: "cat < input.txt > output.txt"
** Expected: [cat]->[<]->[input.txt]->[>]->[output.txt]->NULL
*/
static void	test_redirections(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "cat < input.txt > output.txt";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 5)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Input/Output redirections", passed);
}

/*
** Test: "cat >> file.txt << EOF"
** Expected: [cat]->[>>]->[file.txt]->[<<]->[EOF]->NULL
*/
static void	test_append_heredoc(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "cat >> file.txt << EOF";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 5)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Append and heredoc", passed);
}

/*
** Test: ""
** Expected: NULL (no tokens)
*/
static void	test_empty_input(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "";
	tokens = lexer(input);
	passed = 0;
	if (tokens == NULL)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Empty input", passed);
}

/*
** Test: "     "
** Expected: NULL (spaces ignored)
*/
static void	test_only_spaces(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "     ";
	tokens = lexer(input);
	passed = 0;
	if (tokens == NULL)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Only spaces", passed);
}

/*
* Test: "echo    hello     world"
** Expected: [echo]->[hello]->[world]->NULL
*/
static void	test_multiple_spaces(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "echo    hello     world";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 3)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Multiple spaces", passed);
}

/*
** Test: "cat | grep | wc"
** Expected: [cat]->[|]->[grep]->[|]->[wc]->NULL
*/
static void	test_multiple_pipes(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "cat | grep | wc";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 5)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Multiple pipes", passed);
}

/*
** Test: "cat < in.txt | grep hello | wc -l > out.txt"
** Expected: [cat]->[<]->[in.txt]->[|]->[grep]->[hello]->
**           [|]->[wc]->[-l]->[>]->[out.txt]->NULL
*/
static void	test_complex_command(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "cat < in.txt | grep hello | wc -l > out.txt";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 11)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Complex command", passed);
}

/*
** Test: echo "hello world"
** Expected: [echo]->["hello world"]->NULL (2 tokens, quotes preserved)
*/
static void	test_double_quotes(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "echo \"hello world\"";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 2)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Double quotes", passed);
}

/*
** Test: echo "hello    world"
** Expected: [echo]->["hello    world"]->NULL (spaces preserved)
*/
static void	test_double_quotes_with_spaces(void)
{
	char		*input;
	t_token		*tokens;
	int			passed;

	input = "echo \"hello    world\"";
	tokens = lexer(input);
	passed = 0;
	if (count_tokens(tokens) == 2)
		passed = 1;
	token_clear(&tokens);
	print_test_result("Quotes with multiple spaces", passed);
}

void	run_lexer_tests(void)
{
	print_test_header("LEXER TESTS");
	test_simple_command();
	test_pipe();
	test_redirections();
	test_append_heredoc();
	test_empty_input();
	test_only_spaces();
	test_multiple_spaces();
	test_multiple_pipes();
	test_complex_command();
	test_double_quotes();
	test_double_quotes_with_spaces();
}
