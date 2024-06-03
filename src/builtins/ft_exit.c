#include "../../include/minishell.h"

bool	ft_exit(char **envp, char ***copy_envp)
{
	int		j;
	char	*shlvl;
	char	**tmp;

	tmp = *copy_envp;
	shlvl = ft_getenv("SHLVL", envp);
	j = ft_atoi(shlvl);
	j--;
	shlvl = ft_itoa(j);
	ft_setenv("SHLVL", shlvl, &envp);
	ft_printf("exit\n");
	while (**copy_envp)
	{
		free(**copy_envp);
		(*copy_envp)++;
	}
	free(tmp);
	ft_del_all();
	exit(0);
	return (true);
}
