#include "../include/minishell.h"

// static void	add_node(t_tree *ast, t_tree *node)
// {
// 	t_tree	*tmp;

// 	tmp = ast;
// }

static t_tree	*create_node(t_mini *shell, size_t i, char **envp)
{
	t_tree	*node;

	node = ft_alloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->content = shell->tab_pars[i];
	give_token(node, envp);

	return (node);
}

t_tree	*create_ast(t_mini *shell, char **envp)
{
	t_tree	*ast;
	t_tree	*node;
	size_t	i;

	i = 0;
	ast = ft_alloc(sizeof(t_tree));
	if (!ast)
		return (NULL);
	while (shell->tab_pars[i])
	{
		node = create_node(shell, i, envp);
		(void)node;
//		add_node(ast, node);
		i++;
	}
	return (ast);
}
