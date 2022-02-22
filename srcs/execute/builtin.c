/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:27:48 by min-kang          #+#    #+#             */
/*   Updated: 2022/02/22 19:15:24 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(t_node *node)
{
	char	*cmd;

	cmd = node->args[0];
	if (!ft_strcmp("cd", to_lower(cmd)))
		return (1);
	/*else if (!ft_strcmp("echo", to_lower(cmd)))*/
	else if (!ft_strcmp("env", to_lower(cmd)))
		return (3);
	else if (!ft_strcmp("exit", to_lower(cmd)))
		return (4);
	else if (!ft_strcmp("export", to_lower(cmd)))
		return (5);
	else if (!ft_strcmp("pwd", to_lower(cmd)))
		return (6);
	else if (!ft_strcmp("unset", to_lower(cmd)))
		return (7);
	else
		return (-1);
}

int	builtin_execute(t_node *node, t_app *app)
{
	char	*cmd;

	cmd = node->args[0];
	if (!ft_strcmp("cd", to_lower(cmd)))
	{
		ft_cd(app, node->args[1]);
		return (0);
	}
	/*else if (!ft_strcmp("echo", to_lower(cmd)))*/
	else if (!ft_strcmp("env", to_lower(cmd)))
	{
		ft_env(app);
		return (0);
	}
	else if (!ft_strcmp("exit", to_lower(cmd)))
	{
		ft_exit();
		return (0);
	}
	else if (!ft_strcmp("export", to_lower(cmd)))
	{
		ft_export(app, node->args);
		return (0);
	}
	else if (!ft_strcmp("pwd", to_lower(cmd)))
	{
		ft_pwd();
		return (0);
	}
	else if (!ft_strcmp("unset", to_lower(cmd)))
	{
		ft_unset(app, node->args);
		return (0);
	}
	else
		return (-1);
}