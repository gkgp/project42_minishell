/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 17:28:27 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	init_app(t_app *app)
{
	app->workdir = ft_getcwd();
	app->env = NULL;
}

void	free_app(t_app *app)
{
	free(app->workdir);
	list_clear(&app->env, list_free_keyval);
}
