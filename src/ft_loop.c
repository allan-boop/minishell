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
		{
			ft_printf("\n");
			exit(0);
		}
		prompt_treatment(line, shell, envp, env);
		free(line);
		status = shell->status;
		close_fd(shell->og_stdin);
		close_fd(shell->og_stdout);
		ft_del_all();
	}
}
