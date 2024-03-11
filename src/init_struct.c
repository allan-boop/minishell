#include "../include/minishell.h"

void	init_struct(t_mini **shell)
{
	*shell = malloc(sizeof(t_mini));
	if (!*shell)
	{
		printf(MALLOC_FAIL);
		exit(1);
	}
	(*shell)->i = 0;
}
