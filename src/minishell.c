#include "../include/minishell.h"

int og_stdin;

int	main(int argc, char **argv, char **envp)
{
	og_stdin = dup(STDIN_FILENO);
	(void)argv;
	ft_nb_args(argc);
	ft_loop(envp);
	return (0);
}
