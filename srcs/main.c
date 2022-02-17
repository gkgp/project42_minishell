/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/23 08:02:24 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	res_shell;

char	**get_env(char **envp)
{
	int	i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		new[i] = ft_strdup(envp[i]);
	new[i] = NULL;
	return (new);
}

void	print_token(t_token *tokens)
{
	while (tokens)
	{
		printf("token number : %d===\n", tokens->token);
		//printf("begin? ---- %d\n", tokens->begin);
		if (tokens->content)
			printf("token content : %s===\n", tokens->content);
		printf("==============\n");
		tokens = tokens->next;
	}
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*r;
	t_token	*tokens;
	char	**env;

	(void) argv;
	res_shell = 0;
    if (argc != 1)
        return (0);
	env = get_env(envp);
    while (1)
    {
		r = readline("input: ");
		//add_history
		tokens = lexer(r, env);
		//print_token(tokens);
		res_shell = minishell(tokens, 0, env);
		free(r);
    }
	return (res_shell);
}
