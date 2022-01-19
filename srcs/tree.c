#include "../includes/minishell.h"

typedef struct s_pv{
	int	left;
	int	right;
	int	sum;
} t_pv;

t_tree *create_tree(int value)
{
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	tree->left = NULL;
	tree->right = NULL;
	tree->value = value;
	return (tree);
}

int	paren_error(char *s, int start, int end)
{
	int	i;
	int	count_open;
	int	count_close;

	i = start;
	count_open = 0;
	count_close = 0;
	while (i < end)
	{
		if (s[i] == '(')
			count_open++;
		if (s[i] == ')')
			count_close++;
	}
	if (count_open == count_close)
		return (count_open);
	ft_putstr_fd("parsing error : parenthesis number not corresponding\n", 2);
	return (-1);
}

int	paren_value_left(char *s, int end)
{
	int	i;
	int	sum;
	int	result;

	i = end - 1;
	while (s[i] == ' ')
		i--;
	if (s[i] != ')')
		return (0);
	else
	{
		result = 1;
		sum = 1;
		while (sum)
		{
			if (s[i] == ')')
			{
				result++;
				sum++;
			}
			if (s[i] == '(')
				sum--;
			i--;
		}
	}
	return (result);
}

int paren_value_right(char *s, int start)
{
	int	i;
	int	sum;
	int	result;

	i = start + 1;
	while (s[i] == ' ')
		i++;
	if (s[i] != '(')
		return (0);
	else
	{
		result = 1;
		sum = 1;
		while (sum)
		{
			if (s[i] == '(')
			{
				result++;
				sum++;
			}
			if (s[i] == ')')
				sum--;
			i++;
		}
	}
	return (result);
}

t_pv	paren_value(char *s, int start, int end)
{
	int		flag;
	int		left;
	int		right;
	int		i;
	t_pv	pv;

	if (paren_error(s, 0, start) == -1 || paren_error(s, end, ft_strlen(s)) == -1)
		return (-1);
	pv.left = paren_value_left(s, start);
	pv.right = paren_value_right(s, end);
	pv.sum = pv.left + pv.right;
	return (pv);
}

void	parse_tree(char *s, t_tree **tree)
{
	if (paren_n_error_check(s, 0, ft_strlen(s) - 1) == -1)
		return ;
	if (paren_n_error_check(s, 0, ft_strlen(s) - 1) > 0)



}