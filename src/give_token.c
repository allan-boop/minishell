#include "../include/minishell.h"

static int	define_token_operator(t_tree *node)
{
	if (node->content[0] == '|')
	{
		if (node->content[1] != '\0')
			return (0);
		return (1);
	}
	return (0);
}

void	give_token(t_tree *node)
{
	node->is_operator = false;
	node->is_cmd = false;
	if (define_token_operator(node) == 1)
		node->is_operator = true;
	printf("node->is_operator = %d\n", node->is_operator);
}
