/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:02:10 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/04/12 13:12:55 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(const int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
	{
		return (1);
	}
	return (0);
}

static int	char_is_numeric(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static long int	ft_atoi(const char *str)
{
	long int		nb;
	long int		sign;

	nb = 0;
	sign = 1;
	while (*str != '\0' && ft_isspace(*str))
	{
		str++;
	}
	if (*str != '\0' && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0' && char_is_numeric(*str) == 1)
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb * sign);
}

static int	ft_isnumeric(char *str)
{
	while (str && *str)
	{
		if (!char_is_numeric(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(int pid, char **args)
{
	if (!ft_isnumeric(*args))
	{
		ft_putstr("minshell: exit: ");
		ft_putstr(*args);
		ft_putstr(": numeric argument required\n");
	}
	else if (args[0] && args[1])
	{
		ft_putstr_fd("minshell: exit: too many arguments\n", 2);
		return (0);
	}
	if (pid != 0)
		ft_putstr("exit\n");
	exit(ft_atoi(*args) % 256);
	return (0);
}
