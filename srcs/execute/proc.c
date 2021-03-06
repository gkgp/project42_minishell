/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:20:11 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/12 13:01:51 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proc_child(t_app *app, t_node *node, int fd_in, int *fd)
{
	close(fd[0]);
	if (node->right && node->right->node_type > 1)
		cmd_execute(app, node->left, (int [3]){fd_in, fd[1], 0});
	else
		cmd_execute(app, node, (int [3]){fd_in, STDOUT_FILENO, 0});
}

int	proc_parent(t_app *app, t_node *node, int *fd, pid_t pid)
{
	int	res;
	int	res_child;

	close(fd[1]);
	res = execute_loop(app, node->right, fd[0]);
	close(fd[0]);
	waitpid(pid, &res_child, 0);
	if (res_child == 2)
		res_child += 128;
	else
		res_child = WEXITSTATUS(res_child);
	if (node->right && node->right->node_type > 1)
		return (res);
	return (res_child);
}
