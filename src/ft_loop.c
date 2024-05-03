#include "../include/minishell.h"

void	prompt_treatment(char *line, t_mini *shell,
	char **envp, char ***copy_envp)
{
	int				error;

	if (line[0] != '\0')
	{
		error = ft_parsing(shell, line);
		if (error == 0)
		{
			shell->list = create_list(shell);
			add_history(line);
			ft_copy_envp(*copy_envp, shell);
			if (shell->list->error_parsing == false)
				ft_execution(shell, envp, copy_envp);
		}
	}
}

void	ft_loop(char **envp)
{
	char			*line;
	t_mini			*shell;
	char			**copy_envp;

	ft_signal();
	copy_envp = ft_copy_envp_no_sort(envp);
	while (1)
	{
		shell = ft_alloc(sizeof(t_mini));
		shell->og_stdin = dup(STDIN_FILENO);
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		prompt_treatment(line, shell, envp, &copy_envp);
		free(line);
		ft_del_all();
	}
	free(copy_envp);
}
