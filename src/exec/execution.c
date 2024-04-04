#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, char **argv)
{
	if (ft_strcmp(shell->tab_pars[0], "cd") == 0)
		return (ft_cd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "echo") == 0)
		return (ft_echo(shell));
	else if (ft_strcmp(shell->tab_pars[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(shell->tab_pars[0], "export") == 0)
		return (ft_export(argv, shell, envp));
/*	else if (ft_strcmp(shell->tab_pars[0], "unset") == 0)
		return (ft_unset(shell, envp));
	else if (ft_strcmp(shell->tab_pars[0], "env") == 0)
		return (ft_env(envp));
*/	else if (ft_strcmp(shell->tab_pars[0], "exit") == 0)
		return (ft_exit());
	return (false);
}

void	ft_execution(t_mini *shell, char **envp, char **argv)
{
	if (custom_builtin(shell, envp, argv) == false)
		return ;
//		other_builtin(shell, envp);
}