/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:06:29 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 17:10:12 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	ft_putnbr_rec(unsigned long num)
{
	int	len;

	len = 0;
	if (num >= 10)
		len += ft_putnbr_rec(num / 10);
	ft_putchar_len((num % 10) + '0');
	return (len + 1);
}

int	ft_putunsigned_len(unsigned int n)
{
	unsigned long	num;
	int				len;

	num = n;
	len = 0;
	if (num == 0)
	{
		ft_putchar_len('0');
		return (1);
	}
	len += ft_putnbr_rec(num);
	return (len);
}
