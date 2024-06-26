#include "../include/minishell.h"

void	ft_free_copy_envp(t_env *env)
{
	int	i;

	i = 0;
	while ((*env).copy_envp[i])
	{
		free((*env).copy_envp[i]);
		i++;
	}
	free((*env).copy_envp);
	free(env);
}
