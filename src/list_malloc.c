#include "minishell.h"

void	clear_all(t_malloc_ptr *list_malloc)
{
	while (list_malloc)
	{
		free(list_malloc->ptr);
		list_malloc = list_malloc->next;
	}
}

void	add_node(t_malloc_ptr *list_malloc, void *var)
{
	t_malloc_ptr	new;

	new.ptr = var;
	while (list_malloc->next)
		list_malloc = list_malloc->next;
	list_malloc->next = &new;
}

void	del_node(t_malloc_ptr *list_malloc, void *var)
{
	while (list_malloc && list_malloc->ptr != var)
}

void	*allocator(size_t size, int type, void *ptr)
{
	if (type == NEW)
	{
		
	}
	else if (type == DELETE)
		del_node(list_malloc);
	else if (type == CLEAR)
		clear_all(list_malloc);
}

void	*charmander(int size)
{
	return (allocator(size, NEW, NULL));
}

void	*squirtle()
{
	return (allocator())
}

void	*evee()
{

}

