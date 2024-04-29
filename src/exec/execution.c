#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, char **copy_envp)
{
	if (ft_strcmp(shell->tab_pars[shell->tab_index], "cd") == 0)
		return (ft_cd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "echo") == 0)
		return (ft_echo(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "pwd") == 0)
		return (ft_pwd(envp));
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
	shell->tab_index = 0;
	shell->i = 0;
	while (shell && shell->tab_pars[shell->tab_index] && shell->tab_cmd[shell->i])
	{
		if (shell->tab_pars[shell->tab_index]
			&& (shell->tab_pars[shell->tab_index][0] == '>'
			|| shell->tab_pars[shell->tab_index][0] == '<'))
		{
			shell->tab_index += 2;
			shell->i++;
			continue ;
		}
		else if (shell->tab_pars[shell->tab_index]
			&& shell->tab_pars[shell->tab_index][0] == '|')
			shell->tab_index++;
		if (custom_builtin(shell, envp, copy_envp) == false)
			other_builtin(shell->tab_cmd[shell->i], envp, shell->tab_cmd[shell->i + 1], shell);
		shell->tab_index++;
		shell->i++;
	}
}
