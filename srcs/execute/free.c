/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:52:42 by min-kang          #+#    #+#             */
/*   Updated: 2022/02/22 13:54:21 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preorder_traversal(t_node *node)
{
	printf("====brrr===%d\n", node->node_type);
	if (node->left)
		preorder_traversal(node->left);
	if (node->right)
		preorder_traversal(node->right);
}

void	free_node(t_node *node)
{
	(void) node;
}
