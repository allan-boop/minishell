#include "../../include/minishell.h"

void	add_node_back(t_list_struct **list, t_list_struct *node)
{
	t_list_struct	*last;

	if (!node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = node;
	node->prev = last;
}

void	add_node_front(t_list_struct *list, t_list_struct *node)
{
	if (!list)
	{
		list = node;
		return ;
	}
	node->next = list;
	list->prev = node;
}

void	del_node_list(t_list_struct **list, t_list_struct *node)
{
	t_list_struct	*prev;
	t_list_struct	*next;
	int				i;

	i = 0;
	if (node)
	{
		if (node->next == NULL && node->prev == node)
			i = 1;
		prev = node->prev;
		next = node->next;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		if (node->content)
			ft_del_alloc(node->content);
		node->next = NULL;
		node->prev = NULL;
		ft_del_alloc(node);
	}
	if (i == 1)
		*list = NULL;
	return ;
}

t_list_struct	*create_node_list(t_mini *shell, size_t i)
{
	t_list_struct	*node;

	node = ft_alloc(sizeof(t_list_struct));
	node->content = shell->tab_pars[i];
	give_token(node);
	node->next = NULL;
	node->prev = node;
	return (node);
}

t_list_struct	*create_list(t_mini *shell)
{
	t_list_struct	*list;
	size_t			i;
	t_list_struct	*node;

	i = 0;
	list = ft_alloc(sizeof(t_list_struct));
	list = NULL;
	while (shell->tab_pars[i])
	{
		node = create_node_list(shell, i);
		add_node_back(&list, node);
		i++;
	}
	list->error_parsing = ft_error_parsing(list);
	return (list);
}
