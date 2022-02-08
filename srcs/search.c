#include "minishell.h"

int	continue_or_not(t_node *node, int success)
{
	if (node->node_type == OR)
	{
		if (success)
			return (0);
		else
			return (1);
	}
	else if (node->node_type == AND)
	{
		if (!success)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}