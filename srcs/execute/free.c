/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:52:42 by min-kang          #+#    #+#             */
/*   Updated: 2022/02/21 16:57:00 by gphilipp         ###   ########.fr       */
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
