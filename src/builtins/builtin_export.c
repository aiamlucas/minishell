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
	{
		if (ft_isalpha(argv[0]) || argv[0] == '_')
			return (1);
		return (0);
	}
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
	key = NULL;
	arg_valid = is_valid_argv(argv[1]);
	if (arg_valid)
	{
		value = ft_strchr(argv[1], '=');
		if (value)
		{
			key = ft_substr(argv[1], 0, value - argv[1]);
			value++;
		}
		else
			key = ft_strdup(argv[1]);
		if (key)
			// ft_isalpha(key[i]), ft_isdigit(key[i]), key[i] == '_'
			ft_printf("valid k: %s v: %s\n", key, value);
		else
			return (print_invalid());
	}
	else
		return (print_invalid());
	return (0);
}
