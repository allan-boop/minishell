#include "../include/minishell.h"

void	ft_parsing(t_mini *shell, char *line)
{
	char	**tab_line;

	tab_line = ft_split_shell(line, ' ');
	(void)tab_line;
	(void)shell;
}
