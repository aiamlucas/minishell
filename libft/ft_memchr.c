/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:10:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/05/26 17:16:49 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*ptr;
	unsigned char			c_cast;

	ptr = (unsigned char *)s;
	c_cast = (unsigned char)c;
	while (n-- > 0)
	{
		if (*ptr == c_cast)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
