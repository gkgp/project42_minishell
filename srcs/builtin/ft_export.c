/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:06:21 by gphilipp          #+#    #+#             */
/*   Updated: 2022/02/22 14:06:33 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_app *app, char **args)
{
	char		*str;
	char		*x;
	int			added;
	int			i;

	i = 0;
	while (args[++i])
	{
		str = ft_strdup(args[i]);
		x = ft_strchr(str, '=');
		if (x == 0 || *(x + 1) == '\0' || x == str)
		{
			ft_putstr("bad key=value for ");
			ft_putstr(str);
			ft_putstr("\n");
			free(str);
			return (1);
		}
		*x = '\0';
		added = ft_setenv(app, str, x + 1);
		free(str);
	}
	return (0);
}
