#include "../include/minishell.h"

void	ft_free_all(t_mini *shell, char *line)
{
	free(line);
	free(shell);
}
