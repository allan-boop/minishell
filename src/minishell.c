#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	set_env(envp, &env, argc, argv);
	ft_loop(envp, &env);
	return (0);
}
