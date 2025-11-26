/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:32:50 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 16:58:58 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_int(int num)
{
	return (ft_putnbr_len(num));
}

int	dispatch_int(va_list args)
{
	int		num;

	num = va_arg(args, int);
	return (handle_int(num));
}
