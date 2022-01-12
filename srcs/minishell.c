/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:49:04 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/12 21:36:11 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

			#include <stdio.h>

int	minishell(int argc, char const *argv[])
{
	t_app			app;

	if (argc != 1)
	{
		ft_putstr("\033[0;33mUsage: ./minishell [cmd]\033[0m\n");
		return (1);
	}
	handle_app(&app);
	// handle_app permet d'utiliser get_app() pour avoir la structure app dans
	// n'importe qu'elle fonction (en gros c'est une global mais hacké via une
	// variable static dans).
	//							(tu peux supprimer le commentaire une fois lu)
	init_app(&app);

	//>> test
	printf("working directory: %s\n", app.workdir);
	ft_cd("./test/");
	printf("cd ./test\nworking directory: %s\n", app.workdir);
	// <<
	(void) argv;
	return (0);
}

void	ma_fonction_exemple(void) // voici un exemple d'utilisation de get_app
{
	t_app			*app;

	app = get_app();
}
