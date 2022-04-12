/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:22:04 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/12 14:20:00 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s, int err)
{
	ft_putstr_fd("minshell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	if (err == -2)
		ft_putstr_fd("command not found", 2);
	else if (err == EISDIR)
		ft_putstr_fd("is a directory", 2);
	else
		ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
}

/*
	ft_putstr_fd(strerror(EISDIR), 2);
	"Is a directory" avec un 'i' majuscule :(
*/
