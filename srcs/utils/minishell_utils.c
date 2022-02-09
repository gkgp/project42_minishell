#include "minishell.h"

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void    ft_putstr_fd(char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
        ft_putchar_fd(s[i++], fd);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while ((size_t) i < n)
		str[i++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	int		i;
	char	*result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while ((size_t) i < size * count)
	{
		result[i] = '\0';
		i++;
	}
	return (result);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*result;

	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	ft_putstr(char *s)
{
	while (s && *s)
		write(1, s++, 1);
}


char	*ft_strjoin(char *s1, char *s2, int flag)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = -1;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (s1);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	if (flag)
		free(s1);
	return (result);
}

static int	index_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char		**result;
	char		*start;
	int			i;
	int			len;

	if (!s)
		return (NULL);
	i = 0;
	result = malloc(sizeof(char *) * (index_count(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		len = 0;
		while (*s && *s != c && len++ != -1)
			s++;
		if (*(s - 1) != c)
			result[i++] = ft_substr(start, 0, len);
	}
	result[i] = 0;
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strchr_set(char *s, char *set)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = 0;
		while (set[j])
			if (s[i] == set[j++])
				return (i);
	}
	return (-1);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

int	ft_chr_count(char *s, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c)
			count++;
	return (count);
}
