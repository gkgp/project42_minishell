/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 13:16:15 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

			#include <stdio.h>

void	test(void)
{
	char			**envp;
	int				i;
	t_app			*app;

	app = get_app();
	printf("working directory: %s\n", app->workdir);
	ft_cd("./test/");
	printf("cd ./test\nworking directory: %s\n", app->workdir);
	printf("%s\n", ft_getenv("USER"));
	printf("%d\n", ft_setenv("MOUSTACHE3", "TRUE"));
	printf("%s\n", ft_getenv("MOUSTACHE3"));
	printf("%d\n", ft_export("MOUSTACHE3=VALID"));
	printf("%d\n", ft_unsetenv("MOUSTACHE3"));
	printf("%s\n", ft_getenv("MOUSTACHE3"));
	printf("%d\n", ft_export("COUCOU=O/"));
	ft_env();
	printf("diff:\n");
	envp = list_env_to_2d();
	i = -1;
	while (envp[++i])
	{
		printf("%s\n", envp[i]);
		free(envp[i]);
	}
	free(envp);
}

int	minishell(int argc, char const *argv[], char *const envp[])
{
	t_app			app;

	if (argc != 1)
	{
		ft_putstr("\033[0;33mUsage: ./minishell [cmd]\033[0m\n");
		return (1);
	}
	handle_app(&app);
	init_app(&app);
	init_env(envp);
	(void) argv;
	test();
	free_app(&app);
	return (0);
}
