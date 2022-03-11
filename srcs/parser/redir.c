/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:24:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/03/11 16:47:03 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_begin(t_node **right, char *redir_name)
{
	(*right) = ft_calloc(1, sizeof(t_node));
	(*right)->node_type = 1;
	(*right)->heredoc = ft_calloc(1, sizeof(char *) * 2);
	(*right)->heredoc[0] = ft_strdup(redir_name);
}

void	heredoc_join(t_node **node, char *join)
{
	int		i;
	char	**new;

	if (!(*node)->current_cmd || !(*node)->current_cmd->right)
	{
		if (!(*node)->current_cmd)
		{
			(*node)->current_cmd = ft_calloc(1, sizeof(t_node));
			(*node)->current_cmd->node_type = 2;
		}
		heredoc_begin(&((*node)->current_cmd->right), join);
		if (!(*node)->root)
			(*node)->root = (*node)->current_cmd;
		return ;
	}
	i = 0;
	while ((*node)->current_cmd->left->heredoc[i])
		i++;
	new = ft_calloc(1, sizeof(char *) * (i + 2));
	i = -1;
	while ((*node)->current_cmd->left->args[++i])
		new[i] = (*node)->current_cmd->right->heredoc[i];
	new[i++] = join;
	free((*node)->current_cmd->left->args);
	(*node)->current_cmd->left->args = new;
}

static t_node	*redir_begin(int redir_type, char *redir_name)
{
	int		*new_type;
	char	**new_name;
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	new_type = malloc(sizeof(int) * 2);
	new_type[0] = redir_type;
	new_type[1] = -1;
	new_name = malloc(sizeof(char *) * 2);
	new_name[0] = ft_strdup(redir_name);
	new_name[1] = NULL;
	new->node_type = 1;
	new->redir_type = new_type;
	new->redir_name = new_name;
	return (new);
}

static void	redir_join(t_node *right, int redir_type, char *redir_name)
{
	int		*new_type;
	char	**new_name;
	int		i;

	i = 0;
	while (right->redir_type[i] != -1)
		i++;
	new_type = malloc(sizeof(int) * (i + 2));
	i = 0;
	while (right->redir_name[i])
		i++;
	new_name = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (right->redir_type[++i] != -1)
		new_type[i] = right->redir_type[i];
	new_type[i++] = redir_type;
	new_type[i] = -1;
	i = -1;
	while (right->redir_name[++i])
		new_name[i] = right->redir_name[i];
	new_name[i++] = ft_strdup(redir_name);
	new_name[i] = NULL;
	free2d(right->redir_type, right->redir_name);
	right->redir_type = new_type;
	right->redir_name = new_name;
}

void	parse_redir(t_node **node, t_token **tokens)
{
	if (!(*node)->current_cmd)
	{
		(*node)->current_cmd = ft_calloc(1, sizeof(t_node));
		(*node)->current_cmd->node_type = 2;
	}
	if (!(*node)->current_cmd->right)
		(*node)->current_cmd->right = redir_begin((*tokens)->token,
				(*tokens)->next->content);
	else
		redir_join((*node)->current_cmd->right,
			(*tokens)->token, (*tokens)->next->content);
	*tokens = (*tokens)->next;
}
