/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/19 11:37:39 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

			#include <stdio.h>

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

static int	ft_readline(void)
{
	/*t_cmd			cmd;
	char			**path;
	int				i;*/
	char			*str;

	while (1)
	{
		str = readline("\nminishell-1.0$ ");
		printf("\n###v###\n%s\n###^###", str);
		/*
		cmd.path = parse_path((char *) cmd.envp);
		cmd.envp = (char *) list_env_to_2d();
		parse_input(str, &cmd);
		execute(cmd);
		while (envp[++i])
			free(envp[i]);
		*/
		if (str)
		{
			if (*str)
				add_history(str);
			free(str);
		}
		if (str && ft_strcmp(str, "exit") == 0)
			return (1); // temporaire
	}
}

int	minishell(int argc, char const *argv[], char *const envp[])
{
	t_app			app;

	if (argc != 1)
	{
		ft_putstr("\033[0;33mUsage: ./minishell [cmd]\033[0m\n");
		return (1);
	}
	init_app(&app);
	init_env(&app, envp);
	(void) argv;
	// test(&app);
	ft_readline();
	free_app(&app);
	return (0);
}
