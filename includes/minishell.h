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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_app
{
	char	*workdir;
}			t_app;

typedef struct s_cmd
{
   //char *cmd; je n'ai pas besoin pour l'instant car args[1] peut remplacer celle-ci
   char	*cmd_path; // command with its path
   char **args; // split arguments (including filename)
   char **envp; // envp
   char	**path; // Possible command paths

   // variables pas encore utilisees
   char *redirect_input; // NULL ou la valeur
   char *redirect_output; // NULL ou la valeur
   int read_input; // 0 ou 1 pour <<
   int append_mod; // 0 ou 1 pour >>
   char *pipes; // right part
} t_cmd;

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
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);
void    	ft_putstr_fd(char *s, int fd);

/* parse */
void    parse_input(char *r_data, t_cmd *cmd);
char	**parse_path(char **envp);

#endif
