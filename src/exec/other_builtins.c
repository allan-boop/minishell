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
		if (access(path, F_OK) == 0)
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

int	ft_execve(char *str, char **envp)
{
	char	*path;
	char	**tab_shell;
	int		i;

	i = -1;
	tab_shell = ft_split(str, ' ');
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
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		syntax_error(ERROR_FORK);
		return (false);
	}
	if (pid == 0 && ft_execve(cmd, envp) == -1)
	{
		exit(0);
		return (false);
	}
	if (pid == 0)
		exit(0);
	waitpid(pid, NULL, 0);
	return (true);
}
