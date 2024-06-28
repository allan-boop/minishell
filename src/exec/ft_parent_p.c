#include "../../include/minishell.h"

void	ft_parent_p(char *cmd_next, t_mini *shell, pid_t pid)
{
	if (cmd_next != NULL)
	{
		if (shell->filein == -1)
			dup2(shell->pipe_fd[shell->i_p][0], STDIN_FILENO);
		ft_close_pipefd(shell);
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
