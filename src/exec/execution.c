#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, char **copy_envp)
{
	if (ft_strcmp(shell->tab_pars[shell->tab_index], "cd") == 0)
		return (ft_cd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "echo") == 0)
		return (ft_echo(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "export") == 0)
		return (ft_export(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "unset") == 0)
		return (ft_unset(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "env") == 0)
		return (ft_env(envp, copy_envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "exit") == 0)
		return (ft_exit());
	return (false);
}

void	ft_execution(t_mini *shell, char **envp, char **copy_envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		syntax_error(ERROR_FORK);
		return ;
	}
	shell->tab_index = 0;
	if (pid == 0)
	{
		while (shell->tab_pars[shell->tab_index])
		{
			if (custom_builtin(shell, envp, copy_envp) == true)
				return ;
			else if (other_builtin(shell, envp) == false)
				return ;
		}
	}
	else
		waitpid(pid, &shell->team_envp->last_return, 0);
}
