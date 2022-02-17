
int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;
	int	res;

	res = 0;
	while ((s1[i] || s2[i]) && res == 0 && i < n)
	{
		if (s1[i] != s2[i])
			res = s1[i] - s2[i];
		i++;
	}
	return (res);
}