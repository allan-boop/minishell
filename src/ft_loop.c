#include "../include/minishell.h"

void	ft_loop(char **envp)
{
	char	*line;
	t_mini	shell;

	while (1)
	{
		init_struct(&shell);
		line = readline("pikapika$ ");
		if (line == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		if (line[0] != '\0')
		{
			add_history(line);
			ft_parsing(&shell, line);
			ft_execution(&shell, envp);
		}
		ft_free_all(&shell, line);
	}
}
