#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, char **copy_envp)
{
	if (ft_strcmp(shell->tab_pars[0], "cd") == 0)
		return (ft_cd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "echo") == 0)
		return (ft_echo(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "export") == 0)
		return (ft_export(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "unset") == 0)
		return (ft_unset(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "env") == 0)
		return (ft_env(envp, copy_envp));
	else if (ft_strcmp(shell->tab_pars[0], "exit") == 0)
		return (ft_exit());
	return (false);
}

void	ft_execution(t_mini *shell, char **envp, char **copy_envp)
{
	shell->tab_index = 0;
	if (custom_builtin(shell, envp, copy_envp) == true)
		return ;
//	other_builtin(shell, envp);
}
