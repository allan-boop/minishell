#include "../../include/minishell.h"

bool	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	return (true);
}
