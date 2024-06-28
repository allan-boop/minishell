#include "../include/minishell.h"

void	prompt_treatment(char *line, t_mini *shell,
	char **envp, t_env *env)
{
	int				error;

	if (line[0] != '\0')
	{
		error = ft_parsing(shell, line, env);
		if (error == 0)
		{
			shell->list = create_list(shell);
			add_history(line);
			ft_copy_envp(env, shell);
			if (shell->list->error_parsing == false)
				ft_execution(shell, envp, env);
		}
	}
}

void	ft_loop_readline(t_mini *shell, t_env *env)
{
	close_fd(shell->og_stdin);
	close_fd(shell->og_stdout);
	ft_del_all();
	ft_free_copy_envp(env);
	ft_printf("\n");
	exit(0);
}

void	ft_loop(char **envp, t_env *env)
{
	int				status;
	char			*line;
	t_mini			*shell;

	rl_catch_signals = 0;
	status = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		shell = ft_alloc(sizeof(t_mini));
		ft_init_shell(shell, status);
		line = readline(PROMPT);
		if (line == NULL)
			ft_loop_readline(shell, env);
		prompt_treatment(line, shell, envp, env);
		free(line);
		status = shell->status;
		close_fd(shell->og_stdin);
		close_fd(shell->og_stdout);
		ft_del_all();
	}
}
