#include "../../include/minishell.h"

bool	ft_pwd(char **envp)
{
	char	*path;

	path = ft_getenv("PWD", envp);
	ft_printf("%s\n", path);
	return (true);
}
