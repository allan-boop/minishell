#include "../../include/minishell.h"

char	*clean_var(char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != 2 && str[i] != 3 && str[i] != 34 && str[i] != 39)
		i++;
	var = ft_alloc(i + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != 2 && str[i] != 3 && str[i] != 34 && str[i] != 39)
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = '\0';
	return (var);
}

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
		ft_replace_space_in_str(shell->tab_pars[i], true);
		str = ft_strchr(shell->tab_pars[i], '$');
		if (str)
		{
			j = 0;
			while (str)
			{
				while (shell->tab_pars[i][j] != '$')
					ft_printf("%c", shell->tab_pars[i][j++], 1);
				shell->tab_pars[i][j++] = 'q';
				str = clean_var(str);
				while (shell->tab_pars[i][j] != '\0'
					&& shell->tab_pars[i][j] != '$'
					&& shell->tab_pars[i][j] != ' '
					&& shell->tab_pars[i][j] != 2
					&& shell->tab_pars[i][j] != 3
					&& shell->tab_pars[i][j] != 34
					&& shell->tab_pars[i][j] != 39)
					j++;
				ft_putstr_fd(ft_getenv(str + 1, envp), 1);
				str = ft_strchr(shell->tab_pars[i], '$');
			}
			while (shell->tab_pars[i][j])
				ft_printf("%c", shell->tab_pars[i][j++], 1);
			if (shell->tab_pars[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		else
		{
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
