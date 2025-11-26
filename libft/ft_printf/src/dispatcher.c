/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:15:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/07 14:02:53 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dispatcher(char specifier, va_list args)
{
	if (specifier == 'c')
		return (dispatch_char(args));
	else if (specifier == 's')
		return (dispatch_string(args));
	else if (specifier == 'i' || specifier == 'd')
		return (dispatch_int(args));
	else if (specifier == '%')
		return (dispatch_percent());
	else if (specifier == 'u')
		return (dispatch_unsigned(args));
	else if (specifier == 'X' || specifier == 'x')
		return (dispatch_hex(args, (specifier == 'X')));
	else if (specifier == 'p')
		return (dispatch_pointer(args));
	return (0);
}
