#include "../include/minishell.h"

void	prompt_treatment(char *line, t_mini *shell,
	char **envp, char ***copy_envp)
{
	int				error;

	if (line[0] != '\0')
	{
		error = ft_parsing(shell, line, *copy_envp);
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

static void	ft_init_shell(t_mini *shell, int status)
{
	shell->og_stdout = dup(STDOUT_FILENO);
	if (shell->og_stdout == -1)
	{
		ft_del_all();
		exit(1);
	}
	shell->og_stdin = dup(STDIN_FILENO);
	if (shell->og_stdin == -1)
	{
		ft_del_all();
		exit(1);
	}
	shell->status = status;
}

void	ft_loop(char **envp)
{
	int				status;
	char			*line;
	t_mini			*shell;
	char			**copy_envp;

	copy_envp = ft_copy_envp_no_sort(envp);
	status = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		shell = ft_alloc(sizeof(t_mini));
		ft_init_shell(shell, status);
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		prompt_treatment(line, shell, envp, &copy_envp);
		printf("%s\n", ft_getenv("PWD", copy_envp));
		free(line);
		status = shell->status;
		close(shell->og_stdin);
		close(shell->og_stdout);
		ft_del_all();
	}
}
