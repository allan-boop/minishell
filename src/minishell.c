#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	ft_nb_args(argc);
	ft_loop(envp, argv);
	return (0);
}
