#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	ft_nb_args(argc);
	ft_signal();
	ft_loop(envp);
	return (0);
}
