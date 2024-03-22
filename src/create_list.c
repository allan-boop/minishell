#include "../include/minishell.h"

static void	add_node(t_list *list, t_list *node)
{
	t_list	*last;


}

static t_list	*create_node(t_mini *shell, size_t i)
{
	t_list	*node;

	node = ft_alloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = shell->tab_pars[i];
	node->nb_child = 0;
	node->nb_parent = 0;
	give_token(node);
	node->next = NULL;
	node->prev = NULL;
	node->child = NULL;
	node->parent = NULL;
	return (node);
}

t_list	*create_list(t_mini *shell)
{
	t_list	*list;
	t_list	*node;
	size_t	i;

	i = 0;
	list = ft_alloc(sizeof(t_list));
	if (!list)
		return (NULL);
	while (shell->tab_pars[i])
	{
		node = create_node(shell, i);
		add_node(list, node);
		i++;
	}
	return (list);
}
