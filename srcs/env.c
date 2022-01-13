/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:24:44 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/13 19:44:01 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

			#include <stdio.h>

void	init_env(char *const envp[])
{
	int			i;
	char		*x;
	t_keyval	*keyval;
	t_app		*app;

	app = get_app();
	i = -1;
	while (envp[++i])
	{
		x = ft_strchr(envp[i], '=');
		*x = '\0';
		keyval = malloc(sizeof(t_keyval));
		*keyval = (t_keyval){ft_strdup(envp[i]), ft_strdup(x + 1)};
		list_push(&app->env, keyval);
	}
}

char	*ft_getenv(char *path)
{
	t_list		**plist;
	t_app		*app;

	app = get_app();
	plist = &app->env;
	while (*plist)
	{
		if (ft_strcmp((*(t_keyval *)(*plist)->data).key, path) == 0)
			return ((*(t_keyval *)(*plist)->data).val);
		plist = &((*plist)->next);
	}
	return (NULL);
}
