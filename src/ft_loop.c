#include "../include/minishell.h"

void	prompt_treatment(char *line, t_mini *shell, char **envp, char **argv)
{
	int				error;

	if (line[0] != '\0')
	{
		error = ft_parsing(shell, line);
		if (error == 0)
		{
			shell->list = create_list(shell);
			add_history(line);
			ft_copy_envp(envp, shell);
			if (shell->list->error_parsing == false)
				ft_execution(shell, envp, argv);
		}
	}
}

void	ft_loop(char **envp, char **argv)
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
		prompt_treatment(line, shell, envp, argv);
		free(line);
		ft_del_all();
	}
}
