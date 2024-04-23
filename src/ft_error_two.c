#include "../include/minishell.h"

void	ft_error_malloc(char **tab_shell)
{
	int	i;

	i = 0;
	syntax_error(MALLOC_FAIL);
	while (tab_shell[i])
		free(tab_shell[i++]);
	free(tab_shell);
	return ;
}
