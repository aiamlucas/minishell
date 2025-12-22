/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:53:52 by ssin              #+#    #+#             */
/*   Updated: 2025/12/22 14:21:36 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MACROS_H
# define MINISHELL_MACROS_H

/* Operators char */
# define C_PIPE		'|'
# define C_RED_IN	'<'
# define C_RED_OUT	'>'
# define C_S_QUOTE	'\''
# define C_D_QUOTE	'"'
# define C_EXP		'$'

/* Operators str */
# define STR_PIPE		"|"
# define STR_RED_IN		"<"
# define STR_HEREDOC	"<<"
# define STR_RED_OUT	">"
# define STR_RED_APP	">>"
# define STR_S_QUOTE	"\'"
# define STR_D_QUOTE	"\""
# define STR_EXP		"$"

#endif
