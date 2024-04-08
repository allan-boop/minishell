#include "../../include/minishell.h"

bool	ft_echo(t_mini *shell, char **envp)
{
	int		i;
	bool	n_option;
	int		j;
	char	*str;

	i = 1;
	n_option = false;
	while (shell->tab_pars[i] != NULL)
	{
		if (ft_strcmp(shell->tab_pars[i], "-n") == 0 && i == 1)
		{
			n_option = true;
			i++;
		}
		if (ft_strchr(shell->tab_pars[i], '$') != NULL)
		{
			j = 0;
			str = ft_strchr(shell->tab_pars[i], '$');
			while (shell->tab_pars[i][j] != '$')
			{
				ft_printf("%c", shell->tab_pars[i][j], 1);
				j++;
			}
			if (str)
				ft_putstr_fd(ft_getenv(str + 1, envp), 1);
			else
			{
				ft_putstr_fd(ft_getenv(shell->tab_pars[i] + 1,
						envp), 1);
			}
		}
		else
		{
			ft_replace_space_in_str(shell->tab_pars[i]);
			ft_putstr_fd(shell->tab_pars[i], 1);
			if (shell->tab_pars[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	return (true);
}
