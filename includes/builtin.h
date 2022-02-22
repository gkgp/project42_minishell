/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:29:15 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/02/22 14:12:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_app	t_app;

int			ft_cd(t_app *app, char *path);
int			ft_env(t_app *app);
int			ft_export(t_app *app, char **args);
int			ft_pwd(void);
int			ft_unset(t_app *app, char **args);

#endif
