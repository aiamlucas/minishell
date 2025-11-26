/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/05/26 17:31:22 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**free_all(char **arr, int count)
{
	int	i;

	i = count - 1;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

static char	**split_words(char **result, const char *s, char c, int wc)
{
	int	i;
	int	len;

	i = 0;
	while (*s && i < wc)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		result[i] = ft_substr(s, 0, len);
		if (!result[i])
			return (free_all(result, i));
		s += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wc;

	if (!s)
		return (NULL);
	wc = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!result)
		return (NULL);
	return (split_words(result, s, c, wc));
}
