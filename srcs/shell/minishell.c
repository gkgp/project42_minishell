/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/03/12 19:58:50 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	accept(t_app *app, char *str_cmd)
{
	char			**env;
	t_token			*tokens;
	int				i;

	if (str_cmd && *str_cmd)
		add_history(str_cmd);
	env = list_env_to_2d(app);
	tokens = lexer(str_cmd, env);
	g_res = shell(app, tokens, 0, env);
	free(tokens);
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

static int	ft_readline(t_app *app)
{
	char			*str;

	while (app->stay_alive)
	{
		str = readline("minshell-1.0$ ");
		if (!str)
		{
			ft_putstr("\033[1A");
			ft_putstr(rl_prompt);
			ft_putstr("exit\n");
			return (1);
		}
		accept(app, str);
		if (str)
			free(str);
	}
	return (0);
}

int	minishell(int argc, char const *argv[], char *const envp[])
{
	t_app			app;

	init_app(&app);
	init_env(&app, envp);
	(void) argv;
	init_signal();
	if (argc == 1)
		accept(&app, (char *) argv[0]);
	ft_readline(&app);
	free_app(&app);
	return (0);
}
