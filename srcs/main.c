/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/23 08:02:24 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	cmd_init(t_cmd **cmd, char **envp)
{
	(*cmd)->envp = envp;
	(*cmd)->path = parse_path(envp);
	(*cmd)->in = 0;
	(*cmd)->out = 1;
	(*cmd)->next = NULL;
}

int	main(int argc, char const *argv[], char *const envp[])
{
	return (minishell(argc - 1, &argv[1], envp));
}
