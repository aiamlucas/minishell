/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:25:20 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/05/22 20:32:04 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_negative(long int *num, char *signal, size_t *len)
{
	if (*num < 0)
	{
		*signal = '-';
		*num *= -1;
		(*len)++;
	}
	else
		*signal = '+';
}

static size_t	calculate_length(long int num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	convert_number(char *str, long int num, size_t len, char signal)
{
	long int	div;
	size_t		i;

	div = 1;
	while (num / div >= 10)
		div *= 10;
	i = 0;
	if (signal == '-')
	{
		str[0] = signal;
		i = 1;
	}
	while (div != 0)
	{
		str[i++] = (num / div) % 10 + '0';
		div /= 10;
	}
	str[len] = '\0';
}

char	*ft_itoa(int n)
{
	long int	num;
	char		signal;
	size_t		len;
	char		*str;

	num = n;
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	len = calculate_length(num);
	handle_negative(&num, &signal, &len);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	convert_number(str, num, len, signal);
	return (str);
}
