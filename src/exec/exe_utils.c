#include "../../include/minishell.h"

int	ft_count_quote(char *str)
{
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
	return (j);
}

char	*ft_clean_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_alloc(sizeof(char)
			* (ft_strlen(str) - ft_count_quote(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 2 && str[i] != 3)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

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
		if (path && access(path, F_OK) == 0)
			return (path);
		i++;
	}
	i = -1;
	return (0);
}

char	*find_path_execve_vol_two(char *tab_shell)
{
	if (tab_shell && access(tab_shell, F_OK) == 0)
		return (tab_shell);
	return (0);
}
