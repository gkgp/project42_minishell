/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:02:06 by min-kang          #+#    #+#             */
/*   Updated: 2022/03/11 12:13:53 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_arg_n_var(char *s, int *index, char **envp, int *wflag)
{
	char	*res;
	int		quote;

	res = NULL;
	while (s[*index] && s[*index] != ' ' && is_arg(s[*index]))
	{
		if (s[*index] == '\'' || s[*index] == '\"')
		{
			quote = s[*index];
			while (s[*index] && s[++(*index)] != quote)
			{
				if (s[*index] == '$' && quote == '\"')
					*index = put_var(&res, s, *index, envp);
				else
					res = ft_strfcat(res, s[*index]);
			}
		}
		else if (s[*index] == '$')
			*index = put_var(&res, s, *index, envp);
		else if (s[*index] == '*' && (*wflag)++ >= 0)
			res = ft_strfcat(res, -42);
		else
			res = ft_strfcat(res, s[*index]);
		(*index)++;
	}
	return (res);
}

int	get_arg(t_token **tokens, char *s, int index, char **envp)
{
	t_token			*new;
	int				wflag;
	char			*str;
	int				len;

	len = index;
	wflag = 0;
	str = put_arg_n_var(s, &len, envp, &wflag);
	if (wflag > 0 && rewrite_wildcard(tokens, str))
	{
		free(str);
		return (len);
	}
	new = ft_calloc(1, sizeof(t_token));
	new->token = ARG;
	new->content = str;
	token_addback(tokens, new);
	return (len);
}
