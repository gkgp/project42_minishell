/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:02:06 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/03/11 12:58:54 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	matching(char *pattern, char *file)
{
	if (*pattern == -42)
	{
		if (!*file)
			return (0);
		else if (matching(pattern, file + 1))
			return (1);
	}
	else if (*pattern != *file)
		return (0);
	if (*pattern)
		return (matching(pattern + 1, file + 1));
	return (1);
}

int	rewrite_wildcard(t_token **tokens, char *str)
{
	t_token		*new;
	char		*pwd;
	char		**args;
	int			i;

	i = -1;
	pwd = ft_getcwd();
	args = wildcard(pwd);
	while (args[++i])
	{
		if (str[1] && (ft_strcmp(&str[1], args[i]) != 0
				&& !matching(str, args[i])))
		{
			free(args[i]);
			continue ;
		}
		new = ft_calloc(1, sizeof(t_token));
		new->token = ARG;
		new->content = args[i];
		token_addback(tokens, new);
	}
	free2d(args, pwd);
	return (1);
}
