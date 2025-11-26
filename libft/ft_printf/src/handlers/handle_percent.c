/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:03:09 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/06 17:03:11 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	handle_percent(char c)
{
	return (ft_putchar_len(c));
}

int	dispatch_percent(void)
{
	return (handle_percent('%'));
}
