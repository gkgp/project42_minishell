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


typedef struct s_app
{
	char		*workdir;
	t_list		*env;
}			t_app;



typedef struct s_tree {
   int   value;
   struct s_tree *left;
   struct s_tree *right;
} t_tree;

typedef enum e_token {
   BEGIN,
   ARG,
   CHEVRON_I,
   CHEVRON_O,
   DOUBLE_CHEVRON_I,
   DOUBLE_CHEVRON_O,
   PIPE,
   OR,
   AND,
   PARENTHESE_O,
   PARENTHESE_C
}  e_token;

typedef struct s_redir{
   int           type;
   char           *filename;
   struct s_redir *in;
   struct s_redir *out;
}  t_redir;

typedef struct s_cmd {
   char  **args;
   struct s_redir *redir;
} t_cmd;

typedef struct s_pipe {
   struct s_cmd *cmd;
   struct s_pipe *next;
} t_pipe;

typedef struct s_node {
   struct s_cmd   *cmd;
   struct s_pipe  *pipe;
} t_node;

typedef struct s_tree {
   int         type;
   struct s_node *left;
   struct s_node *right;
} t_tree;

typedef struct s_token {
   enum e_token   token;
   char           *content;
   struct s_token *next;
   struct s_token *prev;
} t_token;

typedef struct s_all {
   struct s_redir *redir;
   struct s_cmd   *cmd;
   struct s_pipe  *pipe;
   struct s_node  *node;
   struct s_tree  *tree;
}  t_all;

/*typedef struct s_cmd
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
} t_cmd;*/

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
