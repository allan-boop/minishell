#include "../../include/minishell.h"

bool	ft_exit(char **envp)
{
	int		j;
	char	*shlvl;

	shlvl = ft_getenv("SHLVL", envp);
	j = ft_atoi(shlvl);
	j--;
	shlvl = ft_itoa(j);
	ft_setenv("SHLVL", shlvl, &envp);
	ft_printf("exit\n");
	ft_del_all();
	exit(0);
	return (true);
}
