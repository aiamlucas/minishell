/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:30:06 by ssin              #+#    #+#             */
/*   Updated: 2026/02/26 15:45:05 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_string(const char *str, t_env *internal_env, int last_exit)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = expanded_length(str, internal_env, last_exit);
	return (expand_variable(str, internal_env, last_exit, len));
}
