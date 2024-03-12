#include "../include/minishell.h"

void	*ft_alloc(int size)
{
	return (malloc_factory(size, NEW, NULL));
}

void	*ft_del_alloc(void *var)
{
	return (malloc_factory(0, DELETE, var));
}

void	*ft_del_all(void)
{
	return (malloc_factory(0, CLEAR, NULL));
}
