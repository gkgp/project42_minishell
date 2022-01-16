/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:24:50 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/23 08:02:31 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***pipe_split(char *input)
{
	int 	count;
	int		i;
	char	***result;
	char	**pipe_div;
	
	pipe_div = ft_split(input, '|');
}

int	parse_arg(t_cmd **cmd, char **input, int start, int end)
{
	int	i;
	int	index;

	
	if (!ft_strcmp(input[end], ">") || !ft_strcmp(input[end], ">>"))
	{}
	else if (!ft_strcmp(input[end], "|"))
	{}
	else if (!ft_strcmp(input[end], "<"))
	{
		(*cmd)->in = open(input[end - 1], O_RDONLY, 0777);

	}
	else if (!ft_strcmp(input[end], "<<"))
	{
		(*cmd)->limiter = ft_strdup(input[end + 1]);
		return (end + 2);
	}
	else
	{
		ft_putstr("Command name error.");
		return (-1);
	}


	(*cmd)->args = malloc(sizeof(char *) * (end - start));
	i = start;
	index = 0;
	while (i < end)
		(*cmd)->args[index++] = input[i++];
	(*cmd)->cmd_path = define_path((*cmd)->args[0], (*cmd)->path);

	if (!ft_strchr(input[end], "|"))
	{
		(*cmd) = (*cmd)->next;
		*cmd = malloc(sizeof(t_cmd));
		return (end + 1);
	}
	else if (!ft_strchr(input[end], ">"))
	{
		(*cmd)->out = open(input[end + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else if (!ft_strchr(input[end], ">>"))
	{
		(*cmd)->out = open(input[end + 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
}

t_cmd	*parse_input(char *r_data, t_cmd **cmd)
{
	char	**input;
	int		i;
	int		j;	
	char	*set;
	t_cmd	*begin;

	begin = *cmd;
	input = ft_split(r_data, ' ');
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (ft_strchr(input[i], set))
		{
			i = parse_arg(cmd, input, j, i);
			j = i + 1;
		}
	}
	return (begin);
}

char	*define_path(char *cmd, char **paths)
{
	char	*path_cmd;
	int		i;

	i = -1;
    path_cmd = NULL;
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], "/", 0);
		path_cmd = ft_strjoin(path_cmd, cmd, 1);
		printf("%s\n", path_cmd);
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
