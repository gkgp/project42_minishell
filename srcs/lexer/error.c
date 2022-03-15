/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:18:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/03/15 21:19:57 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_error(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->token >= CHEVRON_I && tokens->token <= P_OPEN)
			&& !tokens->next)
			return (1);
		if ((tokens->token >= PIPE && tokens->token <= AND)
			&& (tokens->next->token >= PIPE && tokens->next->token <= AND))
			return (2);
		if ((tokens->token == P_CLOSE) && tokens->next->token == ARG)
			return (3);
		tokens = tokens->next;
	}
	return (0);
}

int	lexer_error(t_token *tokens)
{
	if (check_error(tokens))
	{
		ft_putstr_fd("Syntax error.\n", 2);
		return (0);
	}
	return (1);
}