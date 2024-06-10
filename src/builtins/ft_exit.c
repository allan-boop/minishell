#include "../../include/minishell.h"

bool	ft_exit(char **envp, char ***copy_envp, t_mini **shell)
{
	int		j;
	char	*shlvl;
	char	**tmp;

	tmp = *copy_envp;
	shlvl = ft_getenv("SHLVL", envp);
	j = ft_atoi(shlvl);
	j--;
	shlvl = ft_itoa(j);
	ft_setenv_shell("SHLVL", shlvl, &envp);
	ft_printf("exit\n");
	while (**copy_envp)
	{
		free(**copy_envp);
		(*copy_envp)++;
	}
	free(shlvl);
	free(tmp);
	close((*shell)->og_stdin);
	close((*shell)->og_stdout);
	ft_del_all();
	exit(0);
	return (true);
}
