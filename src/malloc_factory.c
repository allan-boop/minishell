#include "../include/minishell.h"

void	clear_all(t_malloc_ptr *list_malloc)
{
	t_malloc_ptr	*tmp;

	while (list_malloc)
	{
		free(list_malloc->ptr);
		tmp = list_malloc;
		list_malloc = list_malloc->next;
		tmp->next = NULL;
		tmp->ptr = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	*create_node(void *new_ptr)
{
	t_malloc_ptr	*new_node;

	new_node = malloc(sizeof(t_malloc_ptr));
	new_node->ptr = new_ptr;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_malloc_ptr *list_malloc, t_malloc_ptr *new)
{
	if (!list_malloc)
	{
		list_malloc = new;
		list_malloc->next = NULL;
		return ;
	}
	while (list_malloc->next)
		list_malloc = list_malloc->next;
	list_malloc->next = new;
}

void	del_node(t_malloc_ptr *list_malloc, void *var)
{
	t_malloc_ptr	*tmp;

	if (!list_malloc)
		return ;
	while (list_malloc->next && list_malloc->ptr != var)
	{
		tmp = list_malloc;
		list_malloc = list_malloc->next;
	}
	if (list_malloc->ptr == var)
	{
		free(list_malloc->ptr);
		if (list_malloc->next)
			tmp->next = list_malloc->next;
		else
			tmp->next = NULL;
		list_malloc->next = NULL;
		free(list_malloc);
		list_malloc = NULL;
	}
}

void	*malloc_factory(size_t size, int type, void *ptr)
{
	static t_malloc_ptr	*list_malloc;
	void				*new_ptr;
	t_malloc_ptr		*new_node;

	if (type == NEW)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			ft_printf(MALLOC_FAIL);
			exit(1);
		}
		new_node = create_node(new_ptr);
		add_node(list_malloc, new_node);
		return (new_ptr);
	}
	else if (type == DELETE)
		del_node(list_malloc, ptr);
	else if (type == CLEAR)
		clear_all(list_malloc);
	return (NULL);
}

void	*ft_alloc(int size)
{
	return (malloc_factory(size, NEW, NULL));
}

void	*ft_del_alloc(void *var)
{
	return (malloc_factory(0, DELETE, var));
}

void	*ft_del_all()
{
	return (malloc_factory(0, CLEAR, NULL));
}
