#include "../include/minishell.h"

void	clear_all(t_malloc_ptr **list_malloc)
{
	t_malloc_ptr	*tmp;
	t_malloc_ptr	*l_m;

	l_m = *list_malloc;
	while (l_m)
	{
		free(l_m->ptr);
		l_m->ptr = NULL;
		tmp = l_m;
		l_m = l_m->next;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	*list_malloc = NULL;
}

void	*create_node(void *new_ptr)
{
	t_malloc_ptr	*new_node;

	new_node = malloc(sizeof(t_malloc_ptr));
	if (!new_node)
	{
		syntax_error(MALLOC_FAIL);
		ft_del_all();
		exit(1);
	}
	new_node->ptr = new_ptr;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_malloc_ptr **list_malloc, t_malloc_ptr *new)
{
	t_malloc_ptr	*l_m;

	l_m = *list_malloc;
	if (!*list_malloc)
	{
		*list_malloc = new;
		(*list_malloc)->next = NULL;
		return ;
	}
	while (l_m->next)
		l_m = l_m->next;
	l_m->next = new;
}

void	del_node(t_malloc_ptr **list_malloc, void *var)
{
	t_malloc_ptr	*tmp;
	t_malloc_ptr	*l_m;

	if (!*list_malloc)
		return ;
	l_m = *list_malloc;
	if (l_m->ptr == var)
	{
		*list_malloc = l_m->next;
		free(l_m->ptr);
		l_m->ptr = NULL;
		free(l_m);
		l_m = NULL;
		return ;
	}
	while (l_m->next && l_m->next->ptr != var)
		l_m = l_m->next;
	tmp = NULL;
	del_if_same(l_m, tmp, var);
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
			ft_del_all();
			exit(1);
		}
		new_node = create_node(new_ptr);
		add_node(&list_malloc, new_node);
		return (new_ptr);
	}
	else if (type == DELETE)
		del_node(&list_malloc, ptr);
	else if (type == CLEAR)
		clear_all(&list_malloc);
	return (NULL);
}
