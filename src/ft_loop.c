#include "../include/minishell.h"

void	ft_loop(char **envp)
{
	char	*line;
	t_mini	*shell;
	t_tree	*list;

	(void)list;
	ft_signal();
	while (1)
	{
		shell = ft_alloc(sizeof(t_mini));
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		if (line[0] != '\0')
		{
			add_history(line);
			ft_parsing(shell, line);
			list = create_list(shell);
			ft_execution(shell, envp);
		}
		free(line);
		ft_del_all();
	}
}
