#include "../include/minishell.h"

void	del_if_same(t_malloc_ptr *l_m, t_malloc_ptr *tmp, void *var)
{
	if (l_m->next && l_m->next->ptr == var)
	{
		tmp = l_m->next;
		l_m->next = tmp->next;
		free(tmp->ptr);
		tmp->ptr = NULL;
		free(tmp);
		tmp = NULL;
	}
}
