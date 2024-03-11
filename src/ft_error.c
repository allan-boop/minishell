#include "../include/minishell.h"

void	ft_nb_args(int argc)
{
	if (argc != 1)
	{
		ft_printf(MANY_ARGS);
		exit (1);
	}
}
