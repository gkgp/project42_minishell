/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/11 11:43:27 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Les includes système sont à faire un à un dans les fichiers .c correspondant
** pour éviter de faire appel à une fonction interdite, exemple strlen au lieu de
** ft_strlen
*/

typedef struct s_app
{
}			t_app;

/* prototypes */
int			minishell(int argc, char const *argv[]);

/* app.c */
t_app		*handle_app(t_app *abc);
t_app		*get_app(void);

/* dep */
void		ft_putstr(char *s);

#endif
