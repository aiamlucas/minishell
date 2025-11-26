/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:03:29 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 17:03:32 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_unsigned(unsigned int num)
{
	return (ft_putunsigned_len(num));
}

int	dispatch_unsigned(va_list args)
{
	unsigned int		num;

	num = va_arg(args, int);
	return (handle_unsigned(num));
}
