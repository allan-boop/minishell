#include "../../include/minishell.h"

static size_t	ft_count_args(t_mini *shell)
{
	size_t		nb_args;
	t_mini		tmp;

	tmp = *shell;
	nb_args = 0;
	while (tmp.tab_pars[tmp.tab_index + 1]
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '|'
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '<'
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '>')
	{
		tmp.tab_index++;
		nb_args++;
	}
	return (nb_args);
}

bool	ft_unset(t_mini *shell, char **envp)
{
	char		*name;
	size_t		len;
	size_t		i;
	size_t		nb_args;

	if (!shell)
		return (false);
	if (shell->tab_pars[shell->tab_index + 1] == NULL)
	{
		syntax_error(NOT_ENOUGH_ARG);
		return (false);
	}
	nb_args = ft_count_args(shell);
	while (nb_args > 0 && shell->tab_pars[shell->tab_index + 1]
		&& shell->tab_pars[shell->tab_index + 1][0] != '|'
		&& shell->tab_pars[shell->tab_index + 1][0] != '<'
		&& shell->tab_pars[shell->tab_index + 1][0] != '>')
	{
		shell->tab_index++;
		nb_args--;
		name = ft_find_name_var(shell->tab_pars[shell->tab_index]);
		len = ft_strlen(name);
		i = 0;
		while (envp[i] && shell->tab_pars[shell->tab_index]
			&& (shell->tab_pars[shell->tab_index][0] != '|'
			&& shell->tab_pars[shell->tab_index][0] != '<'
			&& shell->tab_pars[shell->tab_index][0] != '>'))
		{
			if (ft_strncmp(envp[i], name, len) == 0
				&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			{
				free(envp[i]);
				while (envp[i])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				if (nb_args == 0)
					return (true);
			}
			else
				i++;
		}
	}
	return (false);
}
