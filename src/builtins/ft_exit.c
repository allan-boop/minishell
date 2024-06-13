#include "../../include/minishell.h"

static bool	error_exit(t_mini **shell, int i)
{
	if ((*shell)->tab_pars[(*shell)->tab_index + 1] != NULL
		&& (*shell)->tab_pars[(*shell)->tab_index + 2] != NULL)
		return (true);
	if ((*shell)->tab_pars[(*shell)->tab_index + 1] != NULL)
	{
		while ((*shell)->tab_pars[(*shell)->tab_index + 1][i])
		{
			if (ft_isalpha((*shell)->tab_pars[(*shell)->tab_index + 1][i]))
			{
				ft_printf("exit: %s: numeric argument required\n",
					(*shell)->tab_pars[(*shell)->tab_index + 1]);
				exit(2);
			}
			i++;
		}
	}
	return (false);
}

bool	ft_exit(char **envp, char ***copy_envp, t_mini **shell)
{
	int		j;
	char	*shlvl;
	char	**tmp;
	int		ret_val;

	if (error_exit(shell, 0) == true)
		return (syntax_error(MANY_ARGS));
	tmp = *copy_envp;
	shlvl = ft_getenv("SHLVL", envp);
	j = ft_atoi(shlvl);
	j--;
	ret_val = ft_atoi((*shell)->tab_pars[(*shell)->tab_index + 1]);
	shlvl = ft_itoa(j);
	ft_setenv_shell("SHLVL", shlvl, &envp);
	ft_printf("exit\n");
	while (**copy_envp)
	{
		free(**copy_envp);
		(*copy_envp)++;
	}
	free(shlvl);
	free(tmp);
	close_fd((*shell)->og_stdin);
	close_fd((*shell)->og_stdout);
	ft_del_all();
	ret_val = ret_val % 256;
	exit(ret_val);
	return (true);
}
