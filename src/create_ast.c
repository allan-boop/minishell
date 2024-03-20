#include "../include/minishell.h"

t_tree	*create_ast(t_mini *shell)
{
	t_tree	*ast;

	ast = ft_alloc(sizeof(t_tree));
	if (!ast)
		return (NULL);
	init_ast(shell, ast);
}
