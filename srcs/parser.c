/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:24:50 by min-kang          #+#    #+#             */
/*   Updated: 2022/01/13 13:24:52 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*last_node(t_node *node)
{
	while (node->right)
		node = node->right;
	return (node);
}

char	**arg_begin(char *s)
{
	char	**new;

	new = malloc(sizeof(char *) * 2);
	new[0] = s;
	new[1] = NULL;
	return (new);
}

void	arg_join(t_node **node, char *join)
{
	int		i;
	int 	count;
	char	**new;

	if (!(*node)->current_cmd || !(*node)->current_cmd->left)
	{
		if (!(*node)->current_cmd)
		{
			(*node)->current_cmd = ft_calloc(1, sizeof(t_node));
			(*node)->current_cmd->node_type = 2;
		}
		(*node)->current_cmd->left = ft_calloc(1, sizeof(t_node));
		(*node)->current_cmd->left->node_type = 0;
		(*node)->current_cmd->left->args = arg_begin(join);
		if (!(*node)->root)
			(*node)->root = (*node)->current_cmd;
		return ;
	}
	i = -1;
	count = 0;
	while ((*node)->current_cmd->left->args[++i])
		count++;
	new = malloc(sizeof(char *) * (count + 2));
	i = -1;
	while ((*node)->current_cmd->left->args[++i])
		new[i] = (*node)->current_cmd->left->args[i];
	new[i++] = join;
	new[i] = NULL;
	free((*node)->current_cmd->left->args);
	(*node)->current_cmd->left->args = new;
}

void	parse_cmd(t_node **node, char *new_arg)
{
	t_node	*new;

	if ((*node)->current_cmd)
		arg_join(node, new_arg);
	else
	{
		new = ft_calloc(1, sizeof(t_node));
		new->node_type = 2;
		new->left = ft_calloc(1, sizeof(t_node));
		new->left->node_type = 0;
		new->left->args = arg_begin(new_arg);
		(*node)->current_cmd = new;
		if (!(*node)->root)
			(*node)->root = (*node)->current_cmd;
	}
}

char	**heredoc_begin(char *redir_name)
{
	char	**new;

	new = ft_calloc(1, sizeof(char *) * 2);
	new[0] = ft_strdup(redir_name);
	return (new);
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
		(*node)->current_cmd->right = ft_calloc(1, sizeof(t_node));
		(*node)->current_cmd->right->node_type = 1;
		(*node)->current_cmd->right->heredoc = heredoc_begin(join);
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

t_node	*redir_begin(int redir_type, char *redir_name)
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

void	redir_join(t_node **node, int redir_type, char *redir_name)
{
	int		*new_type;
	char	**new_name;
	int		i;

	i = 0;
	while ((*node)->current_cmd->right->redir_type[i] != -1)
		i++;
	new_type = malloc(sizeof(int) * (i + 2));
	i = 0;
	while ((*node)->current_cmd->right->redir_name[i])
		i++;
	new_name = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*node)->current_cmd->right->redir_type[++i] != -1)
		new_type[i] = (*node)->current_cmd->right->redir_type[i];
	new_type[i++] = redir_type;
	new_type[i] = -1;
	i = -1;
	while ((*node)->current_cmd->right->redir_name[++i])
		new_name[i] = (*node)->current_cmd->right->redir_name[i];
	new_name[i++] = ft_strdup(redir_name);
	new_name[i] = NULL;
	free((*node)->current_cmd->right->redir_type);
	free((*node)->current_cmd->right->redir_name);
	(*node)->current_cmd->right->redir_type = new_type;
	(*node)->current_cmd->right->redir_name = new_name;
}

void	parse_redir(t_node **node, t_token **tokens)
{
	if (!(*node)->current_cmd)
	{
		(*node)->current_cmd = ft_calloc(1, sizeof(t_node));
		(*node)->current_cmd->node_type = 2;
	}
	if (!(*node)->current_cmd->right)
		(*node)->current_cmd->right = redir_begin((*tokens)->token, (*tokens)->next->content);
	else
		redir_join(node, (*tokens)->token, (*tokens)->next->content);
	*tokens = (*tokens)->next;
}

void	parse_pipe(t_node **node)
{
	t_node	*new;
	t_node	*tmp;

	new = ft_calloc(1, sizeof(t_node));
	new->node_type = 3;
	new->left = (*node)->current_cmd;
	(*node)->current_cmd = NULL;
	if ((*node)->current_pipe)
	{
		tmp = last_node((*node)->current_pipe);
		tmp->right = new;
	}
	else
	{
		(*node)->current_pipe = new;
		if ((*node)->root->node_type < 3)
			(*node)->root = (*node)->current_pipe;
	}
}

void	last_cmd(t_node **node)
{
	t_node	*current;

	if ((*node)->current_cmd && ((*node)->current_pipe))
	{
		current = last_node((*node)->root);
		current->right = (*node)->current_cmd;
		(*node)->current_cmd = NULL;
	}
}

t_node	*parser(t_token *tokens, int index)
{
	t_node	*node;
	t_node	*tmp;
	t_token	*begin;

	begin = tokens;
	node = ft_calloc(1, sizeof(t_node));
	tmp = NULL;
	while (tokens && (tokens->index <= index || index == -1))
	{
		if (tokens->token == ARG)
			arg_join(&node, tokens->content);
		else if (tokens->token >= CHEVRON_I && tokens->token <= DOUBLE_CHEVRON_O)
			parse_redir(&node, &tokens);
		else if (tokens->token == PIPE)
			parse_pipe(&node);
		tokens = tokens->next;
	}
	last_cmd(&node);
	return (node);
}

/*void	preorder_traversal(t_node *node)
{
    printf("====%d\n", node->node_type);
	if (node->left && node->node_type > 1)
		preorder_traversal(node->left);
	if (node->right && node->node_type > 1)
		preorder_traversal(node->right);
}

int	main()
{
	char	*s;
	t_token	*tokens;
	t_node	*node;

	while (1)
	{
		s = readline("input: ");
		tokens = lexer(s);
		if (!tokens)
			ft_putstr("Error.\n");
		node = parser(tokens, -1);
		printf("yo\n");
		preorder_traversal(node);
		free(s);
	}
}*/