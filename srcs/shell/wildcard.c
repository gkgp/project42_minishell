/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:30:26 by gphilipp          #+#    #+#             */
/*   Updated: 2022/02/23 09:39:10 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

static int	dirlen(char *dirname)
{	
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir(dirname);
	while (readdir(dir))
		i++;
	return (i);
}

static struct dirent	*ft_readdir(DIR *dir, struct dirent **entries)
{
	*entries = readdir(dir);
	return (*entries);
}

char	**wildcard(char *dirname)
{
	DIR				*dir;
	struct dirent	*entries;
	char			**strs;
	int				i;

	i = 0;
	dir = opendir(dirname);
	strs = malloc(sizeof(char *) * (dirlen(dirname) + 1));
	while (ft_readdir(dir, &entries))
		strs[i++] = ft_strdup(entries->d_name);
	strs[i] = 0;
	closedir(dir);
	i = -1;
	return (strs);
}

/*
int	main(int argc, char **argv)
{
	char			**strs;
	int				i;

	i = 0;
	strs = wildcard(ft_getcwd());
	while (strs[++i])
		printf("%s\n", strs[i]);
	return (0);
}
*/
