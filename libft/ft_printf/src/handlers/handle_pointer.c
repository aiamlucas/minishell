/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:59 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/07 14:46:35 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_pointer(void *p)
{
	return (ft_putpointer_len(p));
}

int	dispatch_pointer(va_list args)
{
	void	*p;

	p = va_arg(args, void *);
	return (handle_pointer(p));
}
