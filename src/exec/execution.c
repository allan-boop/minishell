#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, char ***copy_envp)
{
	if (shell->fileout != -1)
		dup2(shell->fileout, STDOUT_FILENO);
	if (shell->filein != -1)
		dup2(shell->filein, STDIN_FILENO);
	if (ft_strcmp(shell->tab_pars[shell->tab_index], "cd") == 0)
		return (ft_cd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "echo") == 0)
		return (ft_echo(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "pwd") == 0)
		return (ft_pwd(shell, envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "export") == 0)
		return (ft_export(shell, copy_envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "unset") == 0)
		return (ft_unset(shell, copy_envp));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "env") == 0)
		return (ft_env(envp, *copy_envp, shell));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "exit") == 0)
		return (ft_exit(envp));
	return (false);
}

static void	ft_parent(char *cmd_next, t_mini *shell, pid_t pid, int *pipefd)
{
	if (cmd_next != NULL)
	{
		if (shell->filein == -1)
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	else
	{
		if (shell->filein == -1)
			dup2(shell->og_stdin, STDIN_FILENO);
		waitpid(pid, &(shell->status), 0);
		if (WIFSIGNALED(shell->status))
			if (WTERMSIG(shell->status) == SIGQUIT)
				shell->status = 131;
	}
}

bool	ft_execution_core(t_mini *shell, char **envp,
	char ***copy_envp, char *cmd_next)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		syntax_error(ERROR_FORK);
		return (false);
	}
	if (pid == 0)
	{
		inc_shlvl(shell, envp);
		if (cmd_next != NULL && shell->fileout == -1)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (custom_builtin(shell, envp, copy_envp) == false)
			other_builtin(shell->tab_cmd[shell->i], envp);
		exit(1);
	}
	ft_parent(cmd_next, shell, pid, pipefd);
	return (true);
}

static void	ft_exec_logic( t_mini *shell, char **envp
			, char ***copy_envp, int is_p)
{
	while (shell && shell->tab_index < ft_tab_len(shell->tab_pars)
		&& shell->i < ft_tab_len(shell->tab_cmd)
		&& shell->tab_pars[shell->tab_index]
		&& shell->tab_cmd[shell->i])
	{
		if (shell->tab_pars[shell->tab_index]
			&& shell->tab_pars[shell->tab_index][0] == '|')
			shell->tab_index++;
		ft_redirection(shell);
		if (is_p > 1)
			ft_execution_core(shell, envp, copy_envp,
				shell->tab_cmd[shell->i + 1]);
		else if (custom_builtin(shell, envp, copy_envp) == false)
			other_builtin_p(shell->tab_cmd[shell->i],
				envp, shell->tab_cmd[shell->i + 1], shell);
		while (shell->tab_pars[shell->tab_index] != NULL
			&& shell->tab_pars[shell->tab_index][0] != '|')
			shell->tab_index++;
		shell->i++;
	}
}

void	ft_execution(t_mini *shell, char **envp, char ***copy_envp)
{
	int	is_p;

	shell->tab_index = 0;
	shell->i = 0;
	is_p = ft_tab_len(shell->tab_cmd);
	ft_exec_logic(shell, envp, copy_envp, is_p);
	dup2(shell->og_stdin, STDIN_FILENO);
	dup2(shell->og_stdout, STDOUT_FILENO);
	shell->filein = -1;
	shell->fileout = -1;
}
