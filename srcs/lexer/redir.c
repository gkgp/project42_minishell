/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:55:48 by min-kang          #+#    #+#             */
/*   Updated: 2022/03/11 11:57:07 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_input(t_token **tokens, char *s, int index)
{
	t_token	*new;
	int		i;

	new = ft_calloc(1, sizeof(t_token));
	i = index + 1;
	if (s[i] == '<' && i++ >= 0)
	{
		new->token = DOUBLE_CHEVRON_I;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = LIMITER;
		new->next->content = put_arg(s, &i);
	}
	else
	{
		new->token = CHEVRON_I;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = INPUT;
		new->next->content = put_arg(s, &i);
	}
	token_addback(tokens, new);
	return (i);
}

int	redir_output(t_token **tokens, char *s, int index)
{
	int		i;
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	i = index + 1;
	if (s[i] == '>' && i++ >= 0)
	{
		new->token = DOUBLE_CHEVRON_O;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = OUTPUT_A;
		new->next->content = put_arg(s, &i);
	}
	else
	{
		new->token = CHEVRON_O;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = OUTPUT_T;
		new->next->content = put_arg(s, &i);
	}
	token_addback(tokens, new);
	return (i);
}
