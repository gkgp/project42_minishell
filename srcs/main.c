/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/11 11:20:09 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

void	ft_putstr(char *s)
{
	while (s && *s)
		write(1, s++, 1);
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_cmd	cmd; 
    char    *r_data;
	char	**path;
	char	*cmd;

    if (argc != 1)
        return (0);
	cmd.envp = envp;
	cmd.path = parse_path(envp);
    r_data = readline("");
    while (r_data)
    {
        parse_input(r_data, &cmd);
		execute(cmd);
    }
	return (minishell(argc - 1, &argv[1]));
}
