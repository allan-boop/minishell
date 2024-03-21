#include "../include/minishell.h"

// static void	add_node(t_tree *list, t_tree *node)
// {
// 	t_tree	*tmp;

// 	tmp = list;
// }

static t_tree	*create_node(t_mini *shell, size_t i)
{
	t_tree	*node;

	node = ft_alloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->content = shell->tab_pars[i];
	give_token(node);
	return (node);
}

t_tree	*create_list(t_mini *shell)
{
	t_tree	*list;
	t_tree	*node;
	size_t	i;

	i = 0;
	list = ft_alloc(sizeof(t_tree));
	if (!list)
		return (NULL);
	while (shell->tab_pars[i])
	{
		node = create_node(shell, i);
		(void)node;
//		add_node(list, node);
		i++;
	}
	return (list);
}
