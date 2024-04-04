#include "../../include/minishell.h"

bool	ft_echo(t_mini *shell)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	while (shell->tab_pars[i] != NULL)
	{
		if (ft_strcmp(shell->tab_pars[i], "-n") == 0 && i == 1)
		{
			n_option = true;
			i++;
		}
		ft_replace_space_in_str(shell->tab_pars[i]);
		ft_putstr_fd(shell->tab_pars[i], 1);
		if (shell->tab_pars[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	return (true);
}
