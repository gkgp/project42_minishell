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

char	**split_combine(char **s1, char **s2)
{
	int	i;
	int count;
	char	**result;

	i = 0;
	count = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	while (s1[i])
		count++;
	i = 0;
	while (s2[i])
		count++;
	result = malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = 0;
	free(s1);
	free(s2);
	return (result);
}


char	*between_quote(char *input, int start)
{
	int		end;
	char	*result;
	int		i;	
	if (input[start] == '\'')
		end = ft_strchr(input + start + 1, '\'');
	else if (input[start] == '\"')
		end = ft_strchr(input + start + 1, '\"');
	result = malloc(sizeof(char) * (end - start - 1));
	i = 0;
	while (++start < end)
		result[i++] = input[start];
	result[i] = '\0';
	return (result);
}

void parse_redir_input(t_cmd **cmd, int input, int index)
{
	int	i;
	char	*tmp;
	char	*filename;
	char	*quote;
	
	quote = ft_strdup("\"\'");
	if (input[index + 1] == '<')
	{
		tmp = ft_substr(input, 0, index);
		(*cmd)->args = ft_split(tmp);
		free(tmp);
		if (ft_strchar_set(input + index + 1, quote))
		{
			(*cmd)->limiter = between_quote(input, ft_strchar_set(input + index + 1, quote));
			index += ft_strlen((*cmd)->limiter) + 2;
		}
		tmp = ft_split(input + index + 1, ' ');
		(*cmd)->limiter = tmp[0];
		(*cmd)->args = split_combien((*cmd)->args, ++tmp);
		free(--tmp);
	}
	else
	{
		tmp = ft_substr(input, 0 , index);
		(*cmd)->args = ft_split(tmp);
		free(tmp);
		if (ft_strchar_set(input + index + 1, quote))
		{
			filename = between_quote(input, ft_strchar_set(input + index + 1, quote));
			index += ft_strlen(filename) + 2;
		tmp = ft_split(input + index + 1, ' ');
		filename = tmp[0];
		(*cmd)->args = split_combien((*cmd)->args, ++tmp);
		free(--tmp);
	}
	free(quote);
}

void	parse_redir_output(t_cmd **cmd, int input, int index)
{

}

void	parse_arg(t_cmd **cmd, char *input)
{
	char	**args;
	int		i;
	int		j;

	if (ft_strchr(input, '<') >= 0)
		parse_redir_input(cmd, input, ft_strchr(input, '<'));
	else if (ft_strchr(input, '>') >= 0)
		parse_redir_output(cmd, input, ft_strchr(input, '>'));
	else
		args = ft_split(input, ' ');
	i = 0;
	j = 0;
	while (s[i])

	*cmd = (*cmd)->next;
}

char	***pipe_split(t_cmd **cmd, char *input)
{
	int		i;
	char	**pipe_div;
	
	pipe_div = ft_split(input, '|');
	i = 0;
	while (pipe_div[i])
		parse_arg(cmd, pipe_div[i++]);

}

/*int	parse_arg(t_cmd **cmd, char **input, int start, int end)
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
}*/

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
