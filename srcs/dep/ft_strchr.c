/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:58:41 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/13 14:40:49 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *) s;
	while (*str != '\0')
	{
		if (*str == (char) c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (0);
}
