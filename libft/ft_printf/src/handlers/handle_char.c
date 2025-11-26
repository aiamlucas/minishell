/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:15:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/05 00:51:44 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_char(char c)
{
	return (ft_putchar_len(c));
}

int	dispatch_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (handle_char(c));
}
