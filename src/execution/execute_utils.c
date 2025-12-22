/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:51:23 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/12/22 15:54:48 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_input_file(t_redir *redirections)
{
	while (redirections)
	{
		if (redirections->type == TOKEN_REDIR_IN)
			return (redirections->file);
		redirections = redirections->next;
	}
	return (NULL);
}

char	*get_output_file(t_redir *redirections)
{
	while (redirections)
	{
		if (redirections->type == TOKEN_REDIR_OUT
		|| redirections->type == TOKEN_REDIR_APPEND)
			return (redirections->file);
		redirections = redirections->next;
	}
	return (NULL);
}
