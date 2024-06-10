#include "../../include/minishell.h"

bool	ft_pwd(t_mini *shell, char ***envp)
{
	char	*path;

	path = ft_getenv("PWD", *envp);
	ft_printf("%s\n", path);
	shell->status = 0;
	return (true);
}
