/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:28:33 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/05/26 17:18:35 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p_last;

	p_last = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			p_last = s;
		s++;
	}
	if (*s == (char)c)
		p_last = s;
	return ((char *)p_last);
}
