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
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, tab_shell);
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

bool	other_builtin(t_mini *shell, char **envp)
{
	char	*whole_command;
	int		index;

	index = shell->tab_index + 1;
	whole_command = ft_strdup_shell(shell->tab_pars[shell->tab_index]);
	while (shell->tab_pars[index] && shell->tab_pars[index][0] != '|'
		&& shell->tab_pars[index][0] != '\0')
	{
		whole_command = ft_strjoin_shell(whole_command, " ");
		whole_command = ft_strjoin_shell(whole_command, shell->tab_pars[index]);
		index++;
	}
	if (!whole_command)
		return (false);
	if (ft_execve(whole_command, envp) == -1)
		return (false);
	return (true);
}
