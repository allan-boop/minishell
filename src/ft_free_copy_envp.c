#include "../include/minishell.h"

void	ft_free_copy_envp(char **copy_envp)
{
	int	i;

	i = 0;
	while (copy_envp[i])
	{
		free(copy_envp[i]);
		i++;
	}
	free(copy_envp);
}
