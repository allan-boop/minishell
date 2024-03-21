#include "../include/minishell.h"

char	*find_path(char *tab_line, char **envp)
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
		path = ft_strjoin_shell(part_path, tab_line);
		ft_del_alloc(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		ft_del_alloc(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		ft_del_alloc(paths[i]);
	ft_del_alloc(paths);
	return (0);
}
