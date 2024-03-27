#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**copy_envp;

	(void)argv;
	ft_nb_args(argc);
	copy_envp = ft_copy_envp(envp);
	ft_loop(copy_envp);
	return (0);
}
