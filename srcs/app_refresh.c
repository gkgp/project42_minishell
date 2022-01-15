/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_refresh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:49:03 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 17:46:10 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	app_refresh_workdir(t_app *app)
{
	free(app->workdir);
	app->workdir = ft_getcwd();
}
