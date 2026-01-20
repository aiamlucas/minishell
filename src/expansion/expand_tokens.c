/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:33:18 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/01/21 00:25:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stddef.h>


static size_t	expanded_length(const char *str, char **envp, int last_exit)
{
	size_t			total_len;
	size_t			var_len;
	const char		*p;
	const char		*var_start;
	char			**ep;

	(void)last_exit;
	p = str;
	total_len = 0;
	while (*p)
	{
		if (*p != '$')
		{
			total_len++;
			p++;
		}
		else
		{
			p++;
			if (*p == '\0')
			{
				total_len++;
				break ;
			}
			if (!(ft_isalnum(*p) || *p == '_'))
			{
				total_len++;
				continue ;
			}
			var_start = p;
			var_len = 0;
			while (*p && (ft_isalnum(*p) || *p == '_'))
			{
				p++;
				var_len++;
			}
			ep = envp;
			while (*ep)
			{
				if (ft_strncmp(*ep, var_start, var_len) == 0 && (*ep)[var_len] == '=')
				{
					total_len += ft_strlen(*ep + var_len + 1);
					break;
				}
				ep++;
			}
		}
	}
	return (total_len);
}

static char	*expand_variable(const char *str, char **envp, int last_exit, size_t len)
{
	const char	*p;
	const char	*var_start;
	const char	*value;
	char		**ep;
	size_t		total_len;
	size_t		var_len;
	char		*ret;

	(void)last_exit;

	p = str;
	total_len = 0;
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	while (*p)
	{
		if (*p != '$')
		{
			ret[total_len] = *p;
			total_len++;
			p++;
		}
		else
		{
			p++;
			if (*p == '\0')
			{
				ret[total_len++] = '$';
				ret[total_len] = '\0';
				return (ret);
			}
			if (!(ft_isalnum(*p) || *p == '_'))
			{
				ret[total_len++] = '$';
				continue ;
			}
			var_start = p;
			var_len = 0;
			while (*p && (ft_isalnum(*p) || *p == '_'))
			{
				p++;
				var_len++;
			}
			ep = envp;
			while (*ep)
			{
				if (ft_strncmp(*ep, var_start, var_len) == 0 && (*ep)[var_len] == '=')
				{
					value = *ep + var_len + 1;
					while (*value)
					{
						ret[total_len++] = *value;
						value++;
					}
					break;
				}
				ep++;
			}
		}
	}
	ret[total_len] = '\0';
	return (ret);
}

bool	expand_tokens(t_token *tokens, char **envp, int last_exit)
{
	t_token		*current;
	char		*expanded;
	size_t		expanded_len;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{

			expanded_len = expanded_length(current->value, envp, last_exit);
			expanded = expand_variable(current->value, envp, last_exit, expanded_len);
			if (!expanded)
				return false;
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
	return (true);
}
