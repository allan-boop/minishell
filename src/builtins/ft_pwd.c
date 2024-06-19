#include "../../include/minishell.h"

bool	ft_pwd(t_mini *shell, t_env *env)
{
	char	*path;

	path = ft_getenv("PWD", (*env).copy_envp);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	shell->status = 0;
	return (true);
}
