/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:59:40 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/22 19:12:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	execute_single_command(t_command *commands, char **envp)
{
	(void)commands;
	(void)envp;
	printf("Single command execution needs to be implemented");
	return (-1);

}
static void	build_pipe_args(char **args, t_command *commands,
							char *infile, char *outfile)
{
	args[0] = "./minishell";

	if (infile)
		args[1] = infile;
	else
		args[1] = "/dev/stdin";
	args[2] = commands->argv[0];
	args[3] = commands->next->argv[0];
	if (outfile)
		args[4] = outfile;
	else
		args[4] = "/dev/stdout";
}

static int	execute_two_command_pipe(t_command *commands, char **envp)
{
	char	*infile;
	char	*outfile;
	char	*args[5];

	infile = get_input_file(commands->redirections);
	outfile = get_output_file(commands->next->redirections);
	if (!commands->argv[0] || !commands->next->argv[0])
		return (-1);
	build_pipe_args(args, commands, infile, outfile);
	return (create_pipe(5, args, envp));
}

static int	execute_multiple_pipes(t_command *commands, char **envp)
{
	(void)commands;
	(void)envp;
	printf("Multiple pipes not implemented yet....");
	return (-1);
}

int	execute_command(t_command *commands, char **envp)
{
	if (!commands)
		return (-1);
	if (!commands->next)
		return (execute_single_command(commands, envp));
	else if (!commands->next->next)
			return (execute_two_command_pipe(commands,envp));
	else
		return (execute_multiple_pipes(commands, envp));
}




