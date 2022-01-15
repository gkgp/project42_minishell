/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 13:00:11 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Reproduction des fonctions bashs (echo, cd, pwd…)
# include "builtin.h"
# include "list.h"

typedef struct s_app
{
	char		*workdir;
	t_list		*env;
}			t_app;

typedef struct s_keyval
{
	char		*key;
	char		*val;
}			t_keyval;

typedef struct s_cmd
{
	char		*cmd_path;
	char		**args;
	char		**envp;
	char		**path;
}			t_cmd;

/*
	//char *cmd; je n'ai pas besoin pour l'instant car args[1] peut
	             remplacer celle-ci

	// variables pas encore utilisees
	char		*redirect_input; // NULL ou la valeur
	char		*redirect_output; // NULL ou la valeur
	int			read_input; // 0 ou 1 pour <<
	int			append_mod; // 0 ou 1 pour >>
	char		*pipes; // right part
*/

/* prototypes */
int			minishell(int argc, char const *argv[], char *const envp[]);

/* app.c */
t_app		*handle_app(t_app *abc);
t_app		*get_app(void);
void		init_app(t_app *app);
void		free_app(t_app *app);
/* app_refresh.c */
void		app_refresh_workdir(void);

/* builtin/….c utils*/
char		*ft_getcwd(void);

/* env.c */
void		init_env(char *const envp[]);
char		*ft_getenv(char *key);
int			ft_setenv(char *key, char *val);
int			ft_unsetenv(char *key);
void		list_free_keyval(void *data);
char		**list_env_to_2d(void);

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

#endif
