/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/12 21:25:23 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Reproduction des fonctions bashs (echo, cd, pwd…)
# include "builtin.h"

/*
** Les includes système sont à faire un à un dans les fichiers .c correspondant
** pour éviter de faire appel à une fonction interdite, exemple strlen au lieu de
** ft_strlen
*/

typedef struct s_app
{
	char	*workdir;
}			t_app;

/* prototypes */
int			minishell(int argc, char const *argv[]);

/* app.c */
t_app		*handle_app(t_app *abc);
t_app		*get_app(void);
void		init_app(t_app *app);
/* app_refresh.c */
void		app_refresh_workdir(void);

/* dep */
void		ft_putstr(char *s);
int			ft_strlen(const char *s);
char		*ft_strdup(const char *s1);

#endif
