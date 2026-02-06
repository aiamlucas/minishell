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

int	print_invalid(char *msg)
{
	ft_printf("%s", msg);
	return (1);
}

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

int	update_env(char *key, char *value, t_env *internal_env)
{
	t_env	*tmp;
	char	*cp_value;

	if (value)
		cp_value = ft_strdup(value);
	else
		cp_value = ft_strdup("");
	tmp = internal_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = cp_value;
			return (1);
		}
		tmp = tmp->next;
	}
	if (cp_value)
		free(cp_value);
	return (0);
}
