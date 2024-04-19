#include "../../include/minishell.h"

int	ft_count_arg_fork(t_mini *shell)
{
	int	nb_pipe;

	nb_pipe = 0;
	while (shell->list)
	{
		if (shell->list->is_operator || shell->list->is_redir)
		{
			nb_pipe++;
		}
		shell->list = shell->list->next;
	}
	return (nb_pipe + 1);
}
