/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/02/21 17:56:25 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	test(t_app *app)
{
	char			**envp;
	int				i;

	printf("working directory: %s\n", app->workdir);
	ft_cd(app, "./test/");
	printf("cd ./test\nworking directory: %s\n", app->workdir);
	printf("%s\n", ft_getenv(app, "USER"));
	printf("%d\n", ft_setenv(app, "MOUSTACHE3", "TRUE"));
	printf("%s\n", ft_getenv(app, "MOUSTACHE3"));
	printf("%d\n", ft_export(app, "MOUSTACHE3=VALID"));
	printf("%d\n", ft_unsetenv(app, "MOUSTACHE3"));
	printf("%s\n", ft_getenv(app, "MOUSTACHE3"));
	printf("%d\n", ft_export(app, "COUCOU=O/"));
	ft_env(app);
	printf("diff:\n");
	envp = list_env_to_2d(app);
	i = -1;
	while (envp[++i])
	{
		printf("%s\n", envp[i]);
		free(envp[i]);
	}
	free(envp);
}

static void	accept(t_app *app, char *str_cmd)
{
	char			**env;
	t_token			*tokens;

	env = list_env_to_2d(app);
	tokens = lexer(str_cmd, env);
	g_res = shell(tokens, 0, env);
	free(env);
}

static int	ft_readline(t_app *app)
{
	char			*str;

	while (1)
	{
		str = readline("minshell-1.0$ ");
		if (str && *str)
			add_history(str);
		if (!str)
		{
			ft_putstr("\033[1Aminishell-1.0$ exit\n");
			return (1);
		}
		accept(app, str);
		if (str)
			free(str);
	}
}

int	minishell(int argc, char const *argv[], char *const envp[])
{
	t_app			app;

	init_app(&app);
	init_env(&app, envp);
	(void) argv;
	// test(&app);
	init_signal();
	if (argc == 1)
		accept(&app, (char *) argv[0]);
	ft_readline(&app);
	free_app(&app);
	return (0);
}
