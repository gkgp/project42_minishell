/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:29:15 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 11:42:48 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int			ft_cd(char *path);
int			ft_env(void);
int			ft_export(char *str);
int			ft_pwd(void);
int			ft_unset(char *str);

#endif
