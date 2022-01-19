/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/19 15:28:14 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Reproduction des fonctions bashs (echo, cd, pwd…)
# include "builtin.h"
# include "list.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct s_app
{
	char		*workdir;
	t_list		*env;
}			t_app;

typedef struct s_keyval
{
   char     *key;
   char     *val;
}        t_keyval;

typedef struct s_list {
   
   struct s_list *next;
   struct s_list *prev;
} t_list;

typedef struct s_tree {
   int   value;
   struct s_tree *left;
   struct s_tree *right;
} t_tree;

typedef enum s_token {
   BEGIN,
   CMD,
   ARGS,
   INPUT,
   OUTPUT_T,
   OUTPUT_A,
   HEREDOC,
   LIMITER,
   OR,
   AND,
   PARENTHESE_O,
   PARENTHESE_C
}  t_token;

typedef struct s_cmd
{
   //char *cmd; je n'ai pas besoin pour l'instant car args[1] peut remplacer celle-ci
   char  *cmd_path; // command with its path
   char  **args; // split arguments (including filename)
   char  **envp; // envp
   char  **path; // Possible command paths
   int   in;      // file descriptor en cas de redirecton input (!= 0)
   int   out;     // file descriptor en cas de redirection output (!= 1)
   char  *limiter; // limiter en cas de <<
   struct s_cmd   *next; // en cas de presence de pipes
} t_cmd;

/* prototypes */
int			minishell(int argc, char *argv[]);

/* app.c */
void		init_app(t_app *app);
void		free_app(t_app *app);
/* app_refresh.c */
void		app_refresh_workdir(t_app *app);

/* builtin/….c utils*/
char		*ft_getcwd(void);

/* env.c */
void		init_env(t_app *app, char *const envp[]);
char		*ft_getenv(t_app *app, char *key);
int			ft_setenv(t_app *app, char *key, char *val);
int			ft_unsetenv(t_app *app, char *key);
char		**list_env_to_2d(t_app *app);

/* lisr2.c */
void		list_free_keyval(void *data);

/* dep */
void		ft_putstr(char *s);
char		*ft_strcat(char *dest, char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(const char *s);

/* parse */
void		parse_input(char *r_data, t_cmd *cmd);
char		**parse_path(char **envp);

/* signal */
void			init_signal(void);

#endif
