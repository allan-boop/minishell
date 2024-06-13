#include "../../include/minishell.h"

bool	ft_pwd(t_mini *shell, char ***envp)
{
	char	*path;

	path = ft_getenv("PWD", *envp);
	if (path == NULL)
	{
		path = getcwd(NULL, 0);
		printf("%s\n", path);
		free(path);
		shell->status = 0;
		return (true);
	}
	ft_printf("%s\n", path);
	shell->status = 0;
	return (true);
}
