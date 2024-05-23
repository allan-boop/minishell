#include "../../include/minishell.h"

void	inc_shlvl(t_mini *shell, char **envp)
{
	int		j;
	char	*shlvl;

	if (ft_strcmp_shell(shell->tab_cmd[shell->i], "./minishell") == 0)
	{
		shlvl = ft_getenv("SHLVL", envp);
		j = ft_atoi(shlvl);
		j++;
		shlvl = ft_itoa(j);
		ft_setenv("SHLVL", shlvl, &envp);
	}
}
