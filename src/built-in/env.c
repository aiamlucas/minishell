/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:14:00 by ssin              #+#    #+#             */
/*   Updated: 2026/01/05 21:16:17 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*builtin_env(char *name)
{
	char	*env_name;

	env_name = getenv(name);
	if (!env_name)
		perror("Fail getenv"); // call error function
	return (env_name);
}

int	builtin_unset(char *name)
{
	//unsetenv(name);
}

char	*builtin_export(char *name, char *value)

	// setenv(const char *name, const char *value, int overwrite);
}

int	main()
{
	printf("%s", builtin_env("user"));
	return (0);
}
