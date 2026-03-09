/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:46:24 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/09 20:09:42 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Updates:
** state=NORMAL + ' -> SINGLE  (opening single quote)
** state=NORMAL + " -> DOUBLE  (opening double quote)
** state=SINGLE + ' -> NORMAL  (closing single quote)
** state=DOUBLE + " -> NORMAL  (closing double quote)
** Returns true if char was a quote that changed state, 
**         false otherwise.
*/
bool	update_state(t_expand_state *state, char c)
{
	if (*state == EXPAND_NORMAL && c == C_S_QUOTE)
	{
		*state = EXPAND_SINGLE;
		return (true);
	}
	if (*state == EXPAND_NORMAL && c == C_D_QUOTE)
	{
		*state = EXPAND_DOUBLE;
		return (true);
	}
	if (*state == EXPAND_SINGLE && c == C_S_QUOTE)
	{
		*state = EXPAND_NORMAL;
		return (true);
	}
	if (*state == EXPAND_DOUBLE && c == C_D_QUOTE)
	{
		*state = EXPAND_NORMAL;
		return (true);
	}
	return (false);
}

static void	append_char(const char **ptr, t_expand *exp)
{
	exp->result[*exp->position] = **ptr;
	(*exp->position)++;
	(*ptr)++;
}

static void	append_dollar(t_expand *exp)
{
	exp->result[*exp->position] = C_EXP;
	(*exp->position)++;
}

bool	build_if_literal(const char **ptr, t_expand *exp)
{
	if (**ptr != C_EXP)
	{
		append_char(ptr, exp);
		return (true);
	}
	return (false);
}

t_dollar_act	build_dollar(const char **ptr, t_expand *exp, int last_exit)
{
	(*ptr)++;
	if (**ptr == '\0')
	{
		append_dollar(exp);
		return (D_STOP);
	}
	if (*exp->state == EXPAND_SINGLE)
	{
		append_dollar(exp);
		return (D_SKIP);
	}
	if (**ptr == C_QUESTION)
	{
		build_exit_code(exp, last_exit);
		(*ptr)++;
		return (D_SKIP);
	}
	if (!(ft_isalpha(**ptr) || **ptr == '_'))
	{
		append_dollar(exp);
		return (D_SKIP);
	}
	return (D_EXPAND);
}
