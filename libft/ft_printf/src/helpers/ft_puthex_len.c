/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:20:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 23:29:05 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	ft_puthex_rec(unsigned long num, int is_uppercase)
{
	int			len;
	const char	*hex_uppercase;
	const char	*hex_lowercase;
	long		i;

	len = 0;
	hex_uppercase = "0123456789ABCDEF";
	hex_lowercase = "0123456789abcdef";
	if (num >= 16)
		len += ft_puthex_rec(num / 16, is_uppercase);
	i = (num % 16);
	if (is_uppercase)
		ft_putchar_len(hex_uppercase[i]);
	else
		ft_putchar_len(hex_lowercase[i]);
	return (len + 1);
}

int	ft_puthex_len(unsigned int n, int is_uppercase)
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
	len += ft_puthex_rec(num, is_uppercase);
	return (len);
}
