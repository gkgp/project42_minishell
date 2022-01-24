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

void	cmd_begin(t_cmd **cmd, char *s)
{
	char	**split;

	*cmd = malloc(sizeof(cmd));
	split = malloc(sizeof(char *) * 2);
	split[0] = s;
	split[1] = NULL;
	(*cmd)->args = split;
}

void	cmd_join(t_cmd **cmd, char *join)
{
	int		i;
	int		j;	
	int 	count;
	char	**new;

	i = -1;
	count = 0;
	while ((*cmd)->args[++i])
		count++;
	new = malloc(sizeof(char *) * (count + 2));
	i = -1;
	while ((*cmd)->args[++i])
		new[i] = (*cmd)->args[i];
	new[i++] = join;
	new[i] = NULL;
	free((*cmd)->args);
	(*cmd)->args = new;
}

/*
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

/*
1 : <
2 : <<
3 : >
4 : >>
*/

void	redir_input(t_cmd **cmd, char *s)
{
	t_redir	*redir;
	
	if (!*cmd)
		cmd = malloc(sizeof(t_cmd));
	redir = (*cmd)->redir;
	if (!redir)
	{
		redir = malloc(sizeof(t_redir));
		redir->in = NULL;
	}
	while (redir->in)
		redir = redir->in;
	redir->type = 1;
	redir->filename = ft_strdup(s);
	redir->in = malloc(sizeof(t_redir));
	redir->in = NULL;
}

void	redir_heredoc(t_cmd **cmd, char *s)
{
	t_redir	*redir;

	if (!*cmd)
		cmd = malloc(sizeof(t_cmd));
	redir = (*cmd)->redir;
	if (!redir)
	{
		redir = malloc(sizeof(t_redir));
		redir->in = NULL;
	}
	while (redir->in)
		redir = redir->in;
	redir->type = 2;
	redir->filename = ft_strdup(s);
	redir->in = malloc(sizeof(t_redir));
	redir->in = NULL;
}

void	redir_output(t_cmd **cmd, char *s)
{
	t_redir	*redir;
	
	if (!*cmd)
		cmd = malloc(sizeof(t_cmd));
	redir = (*cmd)->redir;
	if (!redir)
	{
		redir = malloc(sizeof(t_redir));
		redir->out = NULL;
	}
	while (redir->out)
		redir = redir->out;
	redir->type = 3;
	redir->filename = ft_strdup(s);
	redir->out = malloc(sizeof(t_redir));
	redir->out = NULL;
}

void	redir_output2(t_cmd **cmd, char *s)
{
	t_redir	*redir;
	
	if (!*cmd)
		cmd = malloc(sizeof(t_cmd));
	redir = (*cmd)->redir;
	if (!redir)
	{
		redir = malloc(sizeof(t_redir));
		redir->out = NULL;
	}
	while (redir->out)
		redir = redir->out;
	redir->type = 4;
	redir->filename = ft_strdup(s);
	redir->out = malloc(sizeof(t_redir));
	redir->out = NULL;
}

void	parse_pipe(t_all **all)
{
	t_pipe	*pipe;
	t_cmd	*new_cmd;

	pipe = (*all)->pipe;
	if (!pipe)
	{
		pipe = malloc(sizeof(t_pipe));
		pipe->next = NULL;
	}
	while (pipe->cmd)
		pipe = pipe->next;
	pipe->cmd = (*all)->cmd;
	new_cmd = NULL;
	(*all)->cmd = new_cmd;
}

void	define_node(t_all **all)
{
	(*all)->node = malloc(sizeof(t_node));
	if (!(*all)->pipe)
		(*all)->node->cmd = (*all)->cmd;
	else
		(*all)->node->pipe = (*all)->pipe;
	(*all)->pipe = NULL;
	(*all)->cmd = NULL;
}

void	put_tree(t_all **all, int flag)
{
	t_tree	*tree;

	tree = (*all)->tree;
	if (!flag)
		tree->left = (*all)->node;
	else
		tree->right = (*all)->node;
	(*all)->node = NULL;
}

void	parse_logic(t_all **all, t_token *tokens, int flag)
{
	t_tree	*tree;
	t_tree	*begin;

	tree = (*all)->tree;
	define_node(&all);
	if (!tree)
	{
		tree = malloc(sizeof(t_tree));
		tree->type = flag;
		tree->left = NULL;
		tree->right = NULL;
	}
	else
	{
		
	}
	if (!tree->left)
		put_tree(&all, 0);
	

	
}

t_all	*parser(t_token *tokens, t_cmd *cmd)
{
	t_all	*all;
	t_token	*begin;

	begin = tokens;
	all = malloc(sizeof(t_all));
	while (tokens)
	{
		if (tokens->token == BEGIN)
			cmd_begin(&all->cmd, tokens->content);
		else if (tokens->token == ARG)
			cmd_join(&all->cmd, tokens->content);
		else if (tokens->token == CHEVRON_I)
			redir_input(&all->cmd, tokens->content);
		else if (tokens->token == DOUBLE_CHEVRON_I)
			redir_heredoc(&all->cmd, tokens->content);
		else if (tokens->token == CHEVRON_O)
			redir_output(&all->cmd, tokens->content);
		else if (tokens->token == DOUBLE_CHEVRON_O)
			redir_output2(&all->cmd, tokens->content);
		else if (tokens->token == PIPE)
			parse_pipe(&all);
		/* bonus
		else if (tokens->token == OR)
		*/
		tokens = tokens->next;
	}
	free(tokens);
	return (all);
}
