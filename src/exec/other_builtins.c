#include "../../include/minishell.h"

int	ft_access_exec(char *path, char **tab_shell, char **envp)
{
	if (!path)
		path = find_path_execve_vol_two(tab_shell[0]);
	if (!path)
	{
		syntax_error(ERROR_PATH);
		return (-1);
	}
	if (access(path, F_OK) == -1 && access(path, X_OK) == -1)
	{
		ft_error_malloc(tab_shell);
		return (-1);
	}
	if (execve(path, tab_shell, envp) == -1)
	{
		syntax_error(ERROR_EXECVE);
		return (-1);
	}
	return (0);
}

int	ft_execve(char *str, char **envp)
{
	char	*path;
	char	**tab_shell;
	int		j;

	ft_replace_space(&str);
	tab_shell = ft_split_shell(str, ' ');
	j = 0;
	while (tab_shell[j])
	{
		tab_shell[j] = ft_clean_quotes(tab_shell[j]);
		j++;
	}
	ft_put_space_between(tab_shell);
	if (!tab_shell)
		return (-1);
	path = find_path_execve(tab_shell[0], envp);
	if (!path && access(tab_shell[0], F_OK) == 0
		&& access(tab_shell[0], X_OK) == 0
		&& tab_shell[0][0] == '.' && tab_shell[0][1] == '/')
		path = ft_strdup_shell(tab_shell[0]);
	if (ft_access_exec(path, tab_shell, envp) == -1)
		return (-1);
	return (0);
}

bool	other_builtin(char *cmd, char **envp)
{
	if (cmd[0] && ft_execve(cmd, envp) == 0)
		return (true);
	return (false);
}

void	ft_parent(pid_t pid, int *pipefd, char *cmd_next, t_mini *shell)
{
	if (cmd_next != NULL)
	{
		if (shell->filein == -1)
			dup2(pipefd[0], STDIN_FILENO);
	}
	else
	{
		if (shell->filein == -1)
			dup2(shell->og_stdin, STDIN_FILENO);
		waitpid(pid, &(shell->status), 0);
		shell->status /= 256;
		if (WIFSIGNALED(shell->status))
		{
			if (WTERMSIG(shell->status) == SIGQUIT)
				shell->status = 131;
		}
	}
	close(pipefd[1]);
	close(pipefd[0]);
}

bool	other_builtin_p(char *cmd, char **envp, char *cmd_next, t_mini *shell)
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
		if (cmd_next != NULL)
			if (shell->fileout == -1)
				dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(shell->og_stdin);
		close(shell->og_stdout);
		if (cmd[0] && ft_execve(cmd, envp) == 0)
			ft_execve(cmd, envp);
		ft_free_copy_envp(envp);
		ft_del_all();
		exit(1);
	}
	ft_parent(pid, pipefd, cmd_next, shell);
	return (true);
}
