#include "../../include/minishell.h"

bool	custom_builtin(t_mini *shell, char **envp, t_env *env)
{
	ft_redir(shell, shell->tab_cmd[shell->i + 1]);
	if (ft_strcmp(shell->tab_pars[shell->tab_index], "cd") == 0)
		return (ft_cd(shell, env));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "echo") == 0)
		return (ft_echo(shell, env));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "pwd") == 0)
		return (ft_pwd(shell, env));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "export") == 0)
		return (ft_export(shell, env));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "unset") == 0)
		return (ft_unset(shell, env));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "env") == 0)
		return (ft_env(envp, env, shell));
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "exit") == 0)
		return (ft_exit(envp, env, &shell));
	return (false);
}

static void	ft_parent_p(char *cmd_next, t_mini *shell, pid_t pid)
{
	if (cmd_next != NULL)
	{
		if (shell->filein == -1)
			dup2(shell->pipe_fd[shell->i_p][0], STDIN_FILENO);
		close_fd(shell->pipe_fd[shell->i_p][1]);
		close_fd(shell->pipe_fd[shell->i_p][0]);
		close_fd(shell->fileout);
	}
	else
	{
		if (shell->filein == -1)
			dup2(shell->og_stdin, STDIN_FILENO);
		waitpid(pid, &(shell->status), 0);
		while (wait(NULL) > 0)
		{
			signal(SIGQUIT, SIG_IGN);
			continue ;
		}
		signal(SIGQUIT, proc_signal_handler);
		if (WIFSIGNALED(shell->status))
			shell->status = WTERMSIG(shell->status) + 128;
		else
			if (WIFEXITED(shell->status))
				shell->status = WEXITSTATUS(shell->status);
		close_fd(shell->pipe_fd[shell->i_p][0]);
		close_fd(shell->pipe_fd[shell->i_p][1]);
	}
}

bool	ft_execution_core(t_mini *shell, char **envp, t_env *env, char *cmd_next)
{
	pid_t	pid;
	int		pipefd[2];

	shell->pipe_fd[shell->i_p] = pipefd;
	pipe(shell->pipe_fd[shell->i_p]);
	pid = fork();
	if (pid == -1)
	{
		syntax_error(ERROR_FORK);
		return (false);
	}
	if (pid == 0)
	{
		inc_shlvl(shell, env);
		if (cmd_next != NULL && shell->fileout == -1)
			dup2(shell->pipe_fd[shell->i_p][1], STDOUT_FILENO);
		if (shell->pipe_fd[shell->i_p][0] != -1)
			close(shell->pipe_fd[shell->i_p][0]);
		if (shell->pipe_fd[shell->i_p][1] != -1)
			close(shell->pipe_fd[shell->i_p][1]);
		if (custom_builtin(shell, envp, env) == false)
			other_builtin(shell->tab_cmd[shell->i], env);
		close_fd(shell->og_stdin);
		close_fd(shell->og_stdout);
		ft_free_copy_envp(env);
		ft_del_all();
		exit(1);
	}
	ft_parent_p(cmd_next, shell, pid);
	return (true);
}

static void	ft_exec_logic( t_mini *shell, char **envp
			, t_env *env, int is_p)
{
	while (shell && shell->tab_index < ft_tab_len(shell->tab_pars)
		&& shell->i < ft_tab_len(shell->tab_cmd)
		&& shell->tab_pars[shell->tab_index]
		&& shell->tab_cmd[shell->i])
	{
		if (shell->tab_pars[shell->tab_index]
			&& shell->tab_pars[shell->tab_index][0] == '|')
			shell->tab_index++;
		ft_redirection(shell);
		signal(SIGINT, proc_signal_handler);
		signal(SIGQUIT, proc_signal_handler);
		close_fd(shell->filein);
		if (is_p > 1)
			ft_execution_core(shell, envp, env,
				shell->tab_cmd[shell->i + 1]);
		else if (custom_builtin(shell, envp, env) == false)
			other_builtin_p(shell->tab_cmd[shell->i],
				env, shell->tab_cmd[shell->i + 1], shell);
		while (shell->tab_pars[shell->tab_index] != NULL
			&& shell->tab_pars[shell->tab_index][0] != '|')
			shell->tab_index++;
		shell->i++;
		shell->i_p++;
	}
}

void	ft_execution(t_mini *shell, char **envp, t_env *env)
{
	int	is_p;

	shell->tab_index = 0;
	shell->i = 0;
	is_p = ft_tab_len(shell->tab_cmd);
	shell->pipe_fd = ft_alloc(sizeof(int *) * is_p + 1);
	while (shell->i < is_p)
	{
		shell->pipe_fd[shell->i] = ft_alloc(2 * sizeof(int));
		shell->i++;
	}
	shell->i = 0;
	shell->i_p = 0;
	if (!shell->pipe_fd)
		exit(1);
	ft_exec_logic(shell, envp, env, is_p);
	dup2(shell->og_stdin, STDIN_FILENO);
	dup2(shell->og_stdout, STDOUT_FILENO);
	shell->filein = -1;
	shell->fileout = -1;
}
