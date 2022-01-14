/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_refresh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:49:03 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/12 21:26:48 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	app_refresh_workdir(void)
{
	t_app			*app;

	app = get_app();
	free(app->workdir);
	app->workdir = ft_pwd();
}
