/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:24:50 by min-kang          #+#    #+#             */
/*   Updated: 2022/01/13 19:18:22 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void    parse_input(char *r_data, t_cmd *cmd)
{
    cmd->args = ft_split(r_data, ' ');
    cmd->cmd_path = define_path(cmd->args[0], cmd->path);
}

char	*define_path(char *cmd, char **paths)
{
	char	*path_cmd;
	int		i;

	i = -1;
    path_cmd = NULL;
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(cmd, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		else
			free(path_cmd);
	}
    return (NULL);
}

char	**parse_path(char **envp)
{
	int		i;
	char	**path_tab;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	path_tab = ft_split(envp[i] + 5, ':');
	return (path_tab);
}*/
