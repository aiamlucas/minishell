/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:09:49 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/10/06 16:09:54 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(int num, int digit, int signal)
{
	if (signal == 1)
	{
		if (num > (INT_MAX - digit) / 10)
			return (1);
	}
	else
	{
		if (num > ((-(long long)INT_MIN) - digit) / 10)
			return (1);
	}
	return (0);
}

static const char	*skip_whitspace(const char *str)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str);
}

static const char	*parse_signal(const char *str, int *signal)
{
	*signal = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*signal = -1;
		str++;
	}
	return (str);
}

int	ft_safe_atoi(const char *str, int *result)
{
	int	signal;
	int	num;
	int	digit;

	num = 0;
	str = skip_whitspace(str);
	str = parse_signal(str, &signal);
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_overflow(num, digit, signal))
			return (0);
		num = num * 10 + digit;
		str++;
	}
	str = skip_whitspace(str);
	if (*str != '\0')
		return (0);
	*result = num * signal;
	return (1);
}
