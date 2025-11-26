/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:44:59 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/07 14:45:06 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	ft_putpointer_rec(unsigned long num)
{
	int			len;
	const char	*hex;
	long		i;

	len = 0;
	hex = "0123456789abcdef";
	if (num >= 16)
		len += ft_putpointer_rec(num / 16);
	i = (num % 16);
	ft_putchar_len(hex[i]);
	return (len + 1);
}

int	ft_putpointer_len(void *p)
{
	unsigned long	ptr;
	int				len;

	if (!p)
		return (ft_putstr_len("(nil)"));
	len = 0;
	ptr = (unsigned long)p;
	len += ft_putstr_len("0x");
	if (ptr == 0)
		len += ft_putchar_len('0');
	else
		len += ft_putpointer_rec(ptr);
	return (len);
}
