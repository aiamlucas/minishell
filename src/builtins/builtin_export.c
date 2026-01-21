/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/21 13:39:38 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_argv(char *argv)
{
	if (!argv)
		return (0);
	else
		return (1);
}

int	print_invalid()
{
	ft_printf("export: invalid arg\n");
	return (1);
}

int	builtin_export(char **argv)
{
	int		arg_valid;
	char	*key;
	char	*value;
	char	**args;

	args = NULL;
	arg_valid = is_valid_argv(argv[1]);
	if (arg_valid)
	{
		if (ft_strchr(argv[1], '='))
		{
			args = ft_split(argv[1], '=');
			key = args[0];
			value = args[1];
			if (key && value)
				ft_printf("valid k: %s v: %s\n", key, value);
			else
				print_invalid();
		}
		else
		print_invalid();
	}
	else
		print_invalid();
}
