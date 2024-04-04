#include "../../include/minishell.h"

bool	ft_echo(t_mini *shell)
{
	int		i;

	i = 1;
	while (shell->tab_pars[i] != NULL)
	{
		ft_putstr_fd(shell->tab_pars[i], 1);
		if (shell->tab_pars[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	return (true);
}