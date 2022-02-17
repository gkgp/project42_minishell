#include "../includes/minishell.h"

int		p_couple(t_token *tokens)
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

void    p_jump(t_token **tokens)
{
    int p_end;
    
    p_end = p_couple(*tokens);
    while ((*tokens)->index != p_end)
        *tokens = (*tokens)->next;
    *tokens = (*tokens)->next;
}

int subshell(t_token *tokens, char **envp)
{
    int     fd[2];
    pid_t   pid;
    int     p_end;
    int     res;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        p_end = p_couple(tokens);
        res = minishell(tokens, p_end, envp);
        write(fd[1], &res, sizeof(res));
    }
    else
    {
        wait(NULL);
        res = read(fd[0], &res, sizeof(res));
    }
    return (res);
}



int minishell(t_token *tokens, int index, char **envp)
{
 	t_node	*node;
	t_token  *begin;
    int     res;

    while (tokens && (tokens->index < index || !index))
    {
        if (tokens->token == P_OPEN)
        {
            res = subshell(tokens, envp);
            p_jump(&tokens);
        }
        else if (tokens->begin)
            begin = tokens;
        if (tokens->token == AND || tokens->token == OR || !tokens->next)
        {
            node = parser(begin, tokens->index);
            res = execute(node, envp);
            if (tokens->next && ((res && tokens->token == AND) || (!res && tokens->token == OR)))
            {
                tokens = tokens->next;
                continue;
            }
            else
                break;
        }
        tokens = tokens->next;
    }
    if (!index)
        free_tokens(tokens);
	return (res);
}
