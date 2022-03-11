/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:25:23 by min-kang          #+#    #+#             */
/*   Updated: 2022/03/11 16:39:35 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	p_couple(t_token *tokens)
{
	int	count;

	count = 1;
	while (count)
	{
		tokens = tokens->next;
		if (tokens->token == P_OPEN)
			count++;
		if (tokens->token == P_CLOSE)
			count--;
	}
	return (tokens->index);
}

static void	p_jump(t_token **tokens)
{
	int	p_end;

	p_end = p_couple(*tokens);
	while ((*tokens)->index != p_end)
		*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
}

static int	subshell(t_app *app, t_token *tokens, char **envp)
{
	pid_t	pid;
	int		p_end;
	int		res;

	pid = fork();
	if (pid == 0)
	{
		p_end = p_couple(tokens);
		res = shell(app, tokens->next, p_end, envp);
		exit(res);
	}
	else
		waitpid(pid, &res, 0);
	return (WEXITSTATUS(res));
}

typedef struct s_abc
{
	t_node	*node;
	t_token	*begin;
	int		res;
	int		subsh;
}			t_abc;

static int	do_shell(t_abc *abc, t_app *app, t_token **tokens, char **envp)
{
	if ((*tokens)->begin)
		abc->begin = (*tokens);
	if ((*tokens)->token == AND || (*tokens)->token == OR
		|| (*tokens)->token == P_CLOSE || !(*tokens)->next)
	{
		if (abc->subsh && ((abc->res && (*tokens)->token == AND)
				|| (!abc->res && (*tokens)->token == OR)))
			return (0);
		else if (abc->subsh && ((!abc->res && (*tokens)->token == AND)
				|| (abc->res && (*tokens)->token == OR)))
		{
			(*tokens) = (*tokens)->next;
			return (1);
		}
		abc->node = parser(abc->begin, (*tokens)->index);
		abc->res = execute(app, abc->node, envp);
		if (!(*tokens)->next || (abc->res && (*tokens)->token == AND)
			|| (!abc->res && (*tokens)->token == OR))
			return (0);
	}
	(*tokens) = (*tokens)->next;
	return (1);
}

int	shell(t_app *app, t_token *tokens, int index, char **envp)
{
	t_abc		abc;

	abc.subsh = 0;
	while (tokens && (tokens->index <= index || !index))
	{
		if (tokens->token == P_OPEN)
		{
			abc.subsh = 0;
			abc.res = subshell(app, tokens, envp);
			p_jump(&tokens);
			abc.subsh++;
			if (!tokens)
				break ;
		}
		if (do_shell(&abc, app, &tokens, envp) == 1)
			continue ;
		else
			break ;
	}
	return (abc.res);
}
