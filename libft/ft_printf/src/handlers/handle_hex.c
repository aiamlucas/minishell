/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:58:36 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 23:35:15 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_hex(unsigned int num, int is_uppercase)
{
	return (ft_puthex_len(num, is_uppercase));
}

int	dispatch_hex(va_list args, int is_uppercase)
{
	unsigned int		num;

	num = va_arg(args, unsigned int);
	return (handle_hex(num, is_uppercase));
}
