/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/02/09 06:57:21 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Reproduction des fonctions bashs (echo, cd, pwd…)
# include "builtin.h"
# include "list.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_app
{
	char		*workdir;
	t_list		*env;
}			t_app;

typedef struct s_keyval
{
	char			*key;
	char			*val;
}			t_keyval;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	char			**envp;
	char			**path;
}			t_cmd;

typedef struct s_tree		t_tree;

typedef struct s_tree {
	int			value;
	t_tree		*left;
	t_tree		*right;
}			t_tree;

enum {
	ARG,
	CHEVRON_I,
	CHEVRON_O,
	DOUBLE_CHEVRON_I,
	DOUBLE_CHEVRON_O,
	PIPE,
	OR,
	AND,
	P_OPEN,
	P_CLOSE,
	INPUT,
	LIMITER,
	OUTPUT_T,
	OUTPUT_A,
	DOLLAR,
	VAR,
	VAR_Q
};

/*
<NODE TYPES>
0 : ARGS
1 : REDIR
2 : CMD
3 : PIPE
*/

typedef struct s_node		t_node;

struct s_node {
	int			node_type;
	char		**args;
	int			*redir_type;
	char		**redir_name;
	char		**heredoc;
	t_node		*left;
	t_node		*right;
	t_node		*root;
	t_node		*current_cmd;
	t_node		*current_pipe;
};

typedef struct s_node		t_token;

struct s_token {
	int			token;
	int			begin;
	int			index;
	char		*content;
	t_token		*next;
};

/* global variable */

/* prototypes */
int			minishell(int argc, char const *argv[], char *const envp[]);

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

/* utils/minishell_utils.c */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char *s, int start, int len);
void		ft_putstr(char *s);
char		*ft_strjoin(char *s1, char *s2, int flag);
char		**ft_split(char *s, char c);
int			ft_strchr_set(char *s, char *set);
int			ft_strchr_num(char *s, char c);
int			ft_chr_count(char *s, char c);

/* lexer */
t_token		*lexer(char *s);

/* parse */
t_node		*parser(t_token *tokens, int index);
void		parse_input(char *r_data, t_cmd *cmd);
char		**parse_path(char **envp);

/* execute */
int			execute(t_node *node, char **envp);
int			cmd_execute(t_node *node, int fd_in, char **envp);

/* free */
void		free_tokens(t_token *tokens);

/* signal */
void		init_signal(void);

#endif
