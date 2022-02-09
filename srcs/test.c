#include "minishell.h"

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

int	redir_input(t_token **tokens, char *s, int index)
{
	int	i;

	i = index;
	if (s[i + 1] == '<')
	{
		(*tokens)->token = DOUBLE_CHEVRON_I;
		*tokens = (*tokens)->next;
		(*tokens)->token = LIMITER;
		(*tokens)->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		(*tokens)->token = CHEVRON_I;
		*tokens = (*tokens)->next;
		(*tokens)->token = INPUT;
		(*tokens)->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	return (i);
}

int	redir_output(t_token **tokens, char *s, int index)
{
	int	i;

	i = index;
	if (s[i + 1] == '>')
	{
		(*tokens)->token = DOUBLE_CHEVRON_O;
		*tokens = (*tokens)->next;
		(*tokens)->token = OUTPUT_A;
		(*tokens)->content = put_arg(s, i + 2);
		i = arg_len(s, i + 2, 0);
	}
	else
	{
		(*tokens)->token = CHEVRON_O;
		*tokens = (*tokens)->next;
		(*tokens)->token = OUTPUT_T;
		(*tokens)->content = put_arg(s, i + 1);
		i = arg_len(s, i + 1, 0);
	}
	return (i);
}

int	give_token(t_token **tokens, int token, int index)
{
	(*tokens)->token = token;
	(*tokens)->next = malloc(sizeof(t_token));
	*tokens = (*tokens)->next;
	return (index);
}

void	*token_add_back(t_token **tokens, t_token *new)
{
	t_token	*begin;

	begin = *tokens;
	if (!*tokens)
		*tokens = new;
	else
	{
		while (*(tokens)->next)
			*tokens = (*tokens)->next;
		(*tokens)->next = new;
	}
	*tokens = begin;
}

int	get_arg(t_token **tokens, char *s, int index)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	new->token = ARG;
	new->content = put_arg(s, index);
	new->next = NULL;
	token_add_back(tokens, new);
	return (arg_len(s, index, 0));
}

// a voir = lorsque la commande commence avec un quote

void	lexer(char *s, t_token **tokens)
{
	int	i;
	t_token	*begin;
	
	i = 0;
	begin = *tokens;
	while (s[i])	
	{
		printf("%d====\n", i);
		while (s[i] == ' ')
			i++;
		if (is_alpha(s[i]))
			i += get_arg(tokens, s, i);
		else if (s[i] == '<')
			i = redir_input(tokens, s, i);
		else if (s[i] == '>')
			i = redir_output(tokens, s, i);
		else if (s[i] == '|' && s[i + 1] != '|')
			i = give_token(tokens, PIPE, i);
		else if (s[i] == '|' && s[i + 1] == '|')
			i = give_token(tokens, OR, i);
		else if (s[i] == '&' && s[i + 1] == '&')
			i = give_token(tokens, AND, i);
		else if (s[i] == '(')
			i = give_token(tokens, PARENTHESE_O, i);
		else if (s[i] == ')')
			i = give_token(tokens, PARENTHESE_C, i);
	}
	*tokens = begin;
}	

int	main()
{
	char	*s;
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	tokens->next = NULL;
	while (1)
	{
		s = readline("input: ");
		lexer(s, &tokens);
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
}