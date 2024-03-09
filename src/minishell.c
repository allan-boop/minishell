#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	ft_error(argc, argv);
	ft_boucle(envp);
	return (0);
}
