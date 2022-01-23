/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:28:00 by min-kang          #+#    #+#             */
/*   Updated: 2022/01/23 19:28:03 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	arg_len(char *s, int index, int flag)
{
	int		i;
	int		count;
	char	c;

	i = index;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				count++;
			if (!s[++i] || s[i] == ' ')
				return (count);
		}
		if (s[i] == '\"')
		{
			while (s[++i] != '\"')
				count++;
			if (!s[++i] || s[i] == ' ')
				return (count);
		}
		i++;
		count++;
	}
	if (flag == 1)
		return (count);
	return (i);
}


char	*put_arg(char *s, int index)
{
	int	count;
	int	i;
	int	j;
	int len;
	char	*result;

	len = arg_len(s, index, 1);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

int	redir_input(t_list **lst, char *s, int index)
{
	int	i;

	i = index;
	if (s[i + 1] = '<')
	{
		(*lst)->token = DOUBLE_CHEVRON_I;
		*lst = (*lst)->next;
		(*lst)->token = LIMITER;
		(*lst)->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		(*lst)->token = CHEVRON_I;
		*lst = (*lst)->next;
		(*lst)->token = INPUT;
		(*lst)->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	return (i);
}

int	redir_output(t_list **lst, char *s, int index)
{
	int	i;

	i = index;
	if (s[i + 1] = '>')
	{
		(*lst)->token = DOUBLE_CHEVRON_O;
		*lst = (*lst)->next;
		(*lst)->token = OUTPUT_A;
		(*lst)->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		(*lst)->token = CHEVRON_O;
		*lst = (*lst)->next;
		(*lst)->token = OUTPUT_T;
		(*lst)->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	return (i);
}

int	give_token(t_list **lst, int token, int index)
{
	(*lst)->token = token;
	(*lst)->next = malloc(sizeof(t_list));
	*lst = (*lst)->next;
	return (index);
}

int	get_arg(t_list **lst, char *s, int index)
{
	(*lst)->token = ARG;
	(*lst)->content = put_arg(s, index);
	(*lst)->next = malloc(sizeof(t_list));
	*lst = (*lst)->next;
	return (arg_len(s, index, 0));
}

// a voir = lorsque la commande commence avec un quote

void	lexer(char *s, t_list **lst)
{
	int	i;
	t_list	*begin;
	
	i = 0;
	begin = *lst;
	while (s[i])	
	{
		while (s[i] == ' ')
			i++;
		if (is_alpha(s[i]))
			i = get_arg(lst, s, i);
		else if (s[i] == '<')
			i = redir_input(lst, s, i);
		else if (s[i] == '>')
			i = redir_out(lst, s, i);
		else if (s[i] == '|' && s[i + 1] != '|')
			i = give_token(lst, PIPE, i);
		else if (s[i] == '|' && s[i + 1] == '|')
			i = give_token(lst, OR, i);
		else if (s[i] == '&' && s[i + 1] == '&')
			i = give_token(lst, AND, i);
		else if (s[i] == '(')
			i = give_token(lst, PARENTHESE_O, i);
		else if (s[i] == ')')
			i = give_token(lst, PARENTHESE_C, i);
	}
	*lst = begin;
}	
