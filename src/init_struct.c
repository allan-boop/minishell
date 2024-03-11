#include "../include/minishell.h"

void	init_struct(t_mini **shell)
{
	*shell = malloc(sizeof(t_mini));
	if (!*shell)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	(*shell)->i = 0;
}
