#include "../../include/minishell.h"

bool	ft_n_option(bool *n_option, bool is_n_option, t_mini *shell, int *i)
{
	int	j;

	while (is_n_option == true)
	{
		j = 0;
		if (shell->tab_pars[*i][j] == '-'
			&& shell->tab_pars[*i][j + 1] == 'n')
		{
			j++;
			while (shell->tab_pars[*i][j] == 'n')
				j++;
			if (shell->tab_pars[*i][j] == '\0')
			{
				*n_option = true;
				(*i)++;
			}
			else
				is_n_option = false;
		}
		else
			is_n_option = false;
	}
	return (false);
}

bool	ft_echo(t_mini *shell)
{
	int		i;
	bool	n_option;
	bool	is_n_option;

	i = 1;
	n_option = false;
	is_n_option = true;
	while (shell->tab_pars[i] != NULL)
	{
		is_n_option = ft_n_option(&n_option, is_n_option, shell, &i);
		ft_replace_space_in_str(shell->tab_pars[i], true);
		i++;
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	return (true);
}
