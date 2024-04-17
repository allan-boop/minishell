#include "../../include/minishell.h"

void	ft_change_path( t_mini *shell, char **envp, char **oldcwd, int i)
{
	if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "-") == 0)
		*oldcwd = ft_getenv("OLDPWD", envp);
	else if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "..") == 0)
	{
		i = ft_strlen(*oldcwd);
		while ((*oldcwd)[i] != '/' && i > 0)
			i--;
		(*oldcwd)[i] = '\0';
	}
	else if (shell->tab_pars[1] == NULL
		|| ft_strcmp(shell->tab_pars[1], "~") == 0)
		*oldcwd = ft_getenv("HOME", envp);
	else
	{
		*oldcwd = ft_strjoin_shell(*oldcwd, "/");
		*oldcwd = ft_strjoin_shell(*oldcwd, shell->tab_pars[1]);
	}
}
