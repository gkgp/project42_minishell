/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:14:24 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 17:34:20 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>

int	ft_cd(t_app *app, char *path)
{
	if (chdir(path) != 0)
		return (errno);
	app_refresh_workdir(app);
	return (0);
}
