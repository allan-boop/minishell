#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	ft_nb_args(argc, argv);
	ft_loop(envp);
	return (0);
}
