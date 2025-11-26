/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:14:36 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/08/21 19:16:29 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int		signal;
	double	result;
	double	factor;

	signal = 1;
	result = 0.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			signal = -1;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		factor = 0.1;
		while (ft_isdigit(*str))
		{
			result += (*str++ - '0') * factor;
			factor *= 0.1;
		}
	}
	return (result * signal);
}
