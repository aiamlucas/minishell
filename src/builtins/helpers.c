/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:31:12 by ssin              #+#    #+#             */
/*   Updated: 2026/02/04 16:31:43 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_key(char *name)
{
	size_t	i;

	if (!*name || ft_strlen(name) == 0)
		return (0);

	i = 0;

	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);

	while (i < ft_strlen(name) && name[i] != '=')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			ft_printf("export: not valid in this context: %s\n", name);
			return (0);
		}
		i++;
	}
	return (1);
}
