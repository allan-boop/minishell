#include "minishell.h"

void	ft_error(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_printf(MANY_ARGS);
		exit (1);
	}
}
