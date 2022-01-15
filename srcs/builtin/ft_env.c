/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:40:03 by gphilipp          #+#    #+#             */
/*   Updated: 2022/01/15 11:43:45 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	t_list		**plist;
	t_keyval	*keyval;
	t_app		*app;

	app = get_app();
	plist = &app->env;
	while (*plist)
	{	
		keyval = (t_keyval *)(*plist)->data;
		ft_putstr(keyval->key);
		ft_putstr("=");
		ft_putstr(keyval->val);
		ft_putstr("\n");
		plist = &((*plist)->next);
	}
	return (0);
}
