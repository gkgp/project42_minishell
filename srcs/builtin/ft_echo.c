/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:37:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/03/14 20:19:41 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_argument(char *str)
{
	if (*str++ != '-')
		return (0);
	while (*str && *str == 'n')
	{
		if (*(str + 1) == 0)
			return (1);
		if (*(str + 1) == 0)
			return (0);
		str++;
	}
	return (0);
}

int	ft_echo(char **args)
{
	int			flag_n;
	int			i;

	if (!args || !*args)
		return (0);
	i = -1;
	flag_n = 0;
	while (args[i + 1] && is_n_argument(args[i + 1]))
	{
		flag_n = 1;
		i++;
	}
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
	return (0);
}
