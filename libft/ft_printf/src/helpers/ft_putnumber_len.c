/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:06:06 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 17:08:02 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	ft_putnbr_rec(long num)
{
	int	len;

	len = 0;
	if (num >= 10)
		len += ft_putnbr_rec(num / 10);
	ft_putchar_len((num % 10) + '0');
	return (len + 1);
}

int	ft_putnbr_len(int n)
{
	long	num;
	int		len;

	num = n;
	len = 0;
	if (num < 0)
	{
		ft_putchar_len('-');
		num = -num;
		len++;
	}
	if (num == 0)
	{
		ft_putchar_len('0');
		return (1);
	}
	len += ft_putnbr_rec(num);
	return (len);
}
