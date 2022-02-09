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

#include "minishell.h"

int	is_arg(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if ((c >= 21 && c <= 64) && c != '$' && c != '&' && c != '(' && c != ')' && c != '*' && c != '<' && c != '>')
		return (1);
	else if ((c >= 91 && c <= 96) || ((c >= 123 && c <= 126) && c != '|'))
		return (1);
	return (0);
}

void	token_addback(t_token **tokens, t_token *new)
{
	t_token	*begin;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	begin = *tokens;
	while ((*tokens)->next)
		*tokens = (*tokens)->next;
	(*tokens)->next = new;
	*tokens = begin;
}

int	arg_len(char *s, int index, int flag)
{
	int		i;
	int		count;

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
				break;
		}
		if (s[i] == '\"')
		{
			while (s[++i] != '\"')
				count++;
			if (!s[++i] || s[i] == ' ')
				break;
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
	int	i;
	int	j;
	int len;
	char	*result;

	len = arg_len(s, index, 1);
	result = ft_calloc(1, sizeof(char) * (len + 1));
	i = index;
	while (s[i] == ' ')
		i++;
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

int	redir_input(t_token **tokens, char *s, int index)
{
	t_token	*new;
	int		i;

	i = index;
	new = ft_calloc(1, sizeof(t_token));
	if (s[i + 1] == '<')
	{
		new->token = DOUBLE_CHEVRON_I;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = LIMITER;
		new->next->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		new->token = CHEVRON_I;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = INPUT;
		new->next->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	token_addback(tokens, new);
	return (i);
}

int	redir_output(t_token **tokens, char *s, int index)
{
	int	i;
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	i = index;
	if (s[i + 1] == '>')
	{
		new->token = DOUBLE_CHEVRON_O;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = OUTPUT_A;
		new->next->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		new->token = CHEVRON_O;
		new->next = ft_calloc(1, sizeof(t_token));
		new->next->token = OUTPUT_T;
		new->next->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	token_addback(tokens, new);
	return (i);
}

int	give_token(t_token **tokens, int token, int index)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	new->token = token;
	token_addback(tokens, new);
	if (token == OR || token == AND)
		return (index + 2);
	else
		return (index + 1);
}

int	get_arg(t_token **tokens, char *s, int index)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	new->token = ARG;
	new->content = put_arg(s, index);
	token_addback(tokens, new);
	return (arg_len(s, index, 0));
}

int	get_var(t_token **tokens, char *s, int index)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	new->token = DOLLAR;
	new->next = malloc(sizeof(t_token));
	new->next->token = VAR;
	new->next->content = put_arg(s, index + 1);
	new->next->next = NULL;
	token_addback(tokens, new);
	return (arg_len(s, index + 1, 0));
}
// a voir = lorsque la commande commence avec un quote
int	lexer_error(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->token >= CHEVRON_I && tokens->token <= P_OPEN) && !tokens->next)
			return (0);
		if ((tokens->token >= PIPE && tokens->token <= AND) && (tokens->next->token >= PIPE && tokens->next->token <= AND))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}

void	put_token_index(t_token **tokens)
{
	t_token	*begin;
	int		index;

	begin = *tokens;
	index = 0;
	while (*tokens)
	{
		(*tokens)->index = index++;
		*tokens = (*tokens)->next;
	}
	*tokens = begin;
}

t_token	*lexer(char *s)
{
	int	i;
	t_token	*tokens;
	
	tokens = NULL;
	i = 0;
	while (i < ft_strlen(s))	
	{
		while (s[i] == ' ')
			i++;
		if (is_arg(s[i]))
			i = get_arg(&tokens, s, i);
		else if (s[i] == '$')
			i = get_var(&tokens, s, i);
		else if (s[i] == '<')
			i = redir_input(&tokens, s, i);
		else if (s[i] == '>')
			i = redir_output(&tokens, s, i);
		else if (s[i] == '|' && s[i + 1] != '|')
			i = give_token(&tokens, PIPE, i);
		else if (s[i] == '|' && s[i + 1] == '|')
			i = give_token(&tokens, OR, i);
		else if (s[i] == '&' && s[i + 1] == '&')
			i = give_token(&tokens, AND, i);
		else if (s[i] == '(')
			i = give_token(&tokens, P_OPEN, i);
		else if (s[i] == ')')
			i = give_token(&tokens, P_CLOSE, i);
	}
	if (!lexer_error(tokens) || i == -1)
	{
		free_tokens(tokens);
		return (NULL);
	}
	put_token_index(&tokens);
	return (tokens);
}	


/*int	main()
{
	char	*s;
	t_token	*tokens;

	while (1)
	{
		s = readline("input: ");
		tokens = lexer(s);
		if (!tokens)
			ft_putstr("Error.\n");
		while (tokens)
		{
			printf("token number : %d===\n", tokens->token);
			if (tokens->content)
				printf("token content : %s===\n", tokens->content);
			printf("==============\n");
			tokens = tokens->next;
		}
		free(s);
	}
}*/