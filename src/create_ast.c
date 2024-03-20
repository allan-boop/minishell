#include "../include/minishell.h"

t_tree	*create_ast(t_mini *shell)
{
	t_tree	*ast;

	ast = ft_alloc(sizeof(t_tree));
	if (!ast)
		return (NULL);
	ft_give_token();
	first_node();
	children_node();
}
