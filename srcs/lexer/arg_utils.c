/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:07:54 by gphilipp          #+#    #+#             */
/*   Updated: 2022/03/16 13:23:26 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_arg(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if ((c >= 22 && c <= 64) && c != '&' && c != '(' && c != ')'
		&& c != '<' && c != '>')
		return (1);
	else if ((c >= 91 && c <= 96) || ((c >= 123 && c <= 126) && c != '|'))
		return (1);
	return (0);
}

int	arg_len(char *s, int i, int flag)
{
	int		count;
	int		quote;

	count = 0;
	while (s[i] == ' ')
		i++;
	if ((!s[i] || !is_arg(s[i])) && flag)
		return (-1);
	while (s[i] && s[i] != ' ' && is_arg(s[i]))
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			while (s[i] && s[++i] != quote)
				count++;
			if (!s[++i] || s[i] == ' ')
				break ;
		}
		else if (s[i++])
			count++;
	}
	if (flag)
		return (count);
	return (i);
}

char	*put_arg(char *s, int index)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = arg_len(s, index, 1);
	if (len == -1)
		return (NULL);
	result = ft_calloc(1, sizeof(char) * (len + 1));
	i = index;
	while (s[i] == ' ')
		i++;
	j = 0;
	while (j < len)
	{
		if (s[i] == '\'')
			while (s[++i] != '\'')
				result[j++] = s[i];
		else if (s[i] == '\"')
			while (s[++i] != '\"')
				result[j++] = s[i];
		else
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return (result);
}

