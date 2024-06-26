#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	set_env(envp, env, argc, argv);
	ft_loop(envp, env);
	return (0);
}
