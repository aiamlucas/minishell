/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:31:17 by ssin              #+#    #+#             */
/*   Updated: 2026/01/05 16:32:03 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*builtin_pwd()
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		perror("Fail getcwd"); // call error function
	return (buf);
}

int	main()
{
	char	*wd;

	wd = builtin_pwd();
	printf("%s\n", wd);
	return (0);
}
