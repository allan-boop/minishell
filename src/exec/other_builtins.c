#include "../../include/minishell.h"

char	*find_path_execve(char *tab_shell, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split_shell(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin_shell(paths[i], "/");
		path = ft_strjoin_shell(part_path, tab_shell);
		free(part_path);
		if (path && access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

char	*ft_clean_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 2 || str[i] == 3)
			j++;
		i++;
	}
	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - j + 1));
	j = 0;
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 2 && str[i] != 3)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

int	ft_execve(char *str, char **envp)
{
	char	*path;
	char	**tab_shell;
	int		i;
	int		j;

	i = -1;
	ft_replace_space(&str);
	tab_shell = ft_split(str, ' ');
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
	if (!path)
	{
		while (tab_shell[++i])
			free(tab_shell[i]);
		free(tab_shell);
		syntax_error(ERROR_PATH);
		return (-1);
	}
	if (access(path, F_OK) == -1)
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

bool	other_builtin(char *cmd, char **envp)
{
	if (ft_execve(cmd, envp) == 0)
		return (true);
	return (false);
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
		if (cmd_next != NULL)
			if (shell->fileout == -1)
				dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		ft_execve(cmd, envp);
		exit(1);
	}
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
		{
			if (WTERMSIG(shell->status) == SIGQUIT)
				shell->status = 131;
		}
	}
	return (true);
}
