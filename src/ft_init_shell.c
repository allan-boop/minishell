#include "../include/minishell.h"

void	ft_init_shell(t_mini *shell, int status)
{
	shell->og_stdout = dup(STDOUT_FILENO);
	if (shell->og_stdout == -1)
	{
		ft_del_all();
		close(shell->og_stdout);
		close(shell->og_stdin);
		exit(1);
	}
	shell->og_stdin = dup(STDIN_FILENO);
	if (shell->og_stdin == -1)
	{
		ft_del_all();
		close(shell->og_stdin);
		close(shell->og_stdout);
		exit(1);
	}
	shell->status = status;
}
