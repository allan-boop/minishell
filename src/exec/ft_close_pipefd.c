#include "../../include/minishell.h"

void	ft_close_pipefd(t_mini *shell)
{
	close_fd(shell->pipe_fd[shell->i_p][1]);
	close_fd(shell->pipe_fd[shell->i_p][0]);
	close_fd(shell->fileout);
}

void	ft_close_pipefd_bis(t_mini *shell, int pipefd[2])
{
	close_fd(pipefd[0]);
	close_fd(pipefd[1]);
	close_fd(shell->og_stdin);
	close_fd(shell->og_stdout);
}
