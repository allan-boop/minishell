#include "../include/minishell.h"

void	prompt_treatment(char *line, t_mini *shell, char **envp)
{
	int				error;
	t_list_struct	*list;

	if (line[0] != '\0')
	{
		add_history(line);
		error = ft_parsing(shell, line);
		if (error == 0)
		{
			list = create_list(shell);
			if (list->error_parsing == false)
				ft_execution(shell, envp);
		}
	}
}

void	ft_loop(char **envp)
{
	char			*line;
	t_mini			*shell;

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
		prompt_treatment(line, shell, envp);
		free(line);
		ft_del_all();
	}
}
