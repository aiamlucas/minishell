/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:37:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/05 00:52:07 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_string(char *str)
{
	return (ft_putstr_len(str));
}

int	dispatch_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	return (handle_string(str));
}
