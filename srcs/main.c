/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 13:47:08 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"

void	ft_putstr(char *s)
{
	while (s && *s)
		write(1, s++, 1);
}

int	main(int argc, char const *argv[], char *const envp[])
{
	return (minishell(argc - 1, &argv[1], envp));
}
