/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:06:21 by gphilipp          #+#    #+#             */
/*   Updated: 2022/01/15 11:47:50 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char *s1)
{
	char		*str;
	char		*x;
	int			added;

	str = ft_strdup(s1);
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
	added = ft_setenv(str, x + 1);
	free(str);
	return (0);
}
