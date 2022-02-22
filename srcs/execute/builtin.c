/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:27:48 by min-kang          #+#    #+#             */
/*   Updated: 2022/02/22 14:14:15 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_execute(t_node *node, t_app *app)
{
	char	*cmd;

	cmd = node->args[0];
	if (!ft_strcmp("cd", to_lower(cmd)))
		return (ft_cd(app, node->args[1]));
	/*else if (!ft_strcmp("echo", to_lower(cmd)))*/
	else if (!ft_strcmp("env", to_lower(cmd)))
		return (ft_env(app));
	else if (!ft_strcmp("exit", to_lower(cmd)))
		return (ft_exit());
	else if (!ft_strcmp("export", to_lower(cmd)))
		return (ft_export(app, ft_export(app, node->args)));
	else if (!ft_strcmp("pwd", to_lower(cmd)))
		return (ft_pwd());
	else if (!ft_strcmp("unset", to_lower(cmd)))
		return (ft_unset(app, node->args));
	else
		return (0);
}