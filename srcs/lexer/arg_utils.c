/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:07:54 by gphilipp          #+#    #+#             */
/*   Updated: 2022/03/11 11:59:46 by gphilipp         ###   ########.fr       */
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

static int	arg_len(char *s, int i, int flag)
{
	int		count;
	int		quote;

	count = 0;
	while (s[i] == ' ')
		i++;
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

char	*put_arg(char *s, int *index)
{
	int		j;
	int		len;
	char	*result;
	int		quote;

	len = arg_len(s, *index, 1);
	result = ft_calloc(1, sizeof(char) * (len + 1));
	while (s[*index] == ' ')
		(*index)++;
	j = 0;
	while (j < len)
	{
		if (s[*index] == '\'' || s[*index] == '\"')
		{
			quote = s[*index];
			while (s[*index] && s[++(*index)] != quote)
				result[j++] = s[*index];
		}
		else
			result[j++] = s[(*index)++];
	}
	result[j] = '\0';
	return (result);
}
