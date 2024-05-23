#include "../../include/minishell.h"

static char	**ft_own_args(char ***own_arg, char **copy_envp, int i)
{
	int		k;
	char	**new_envp;

	k = 0;
	new_envp = ft_alloc(sizeof(char *) * (ft_tab_len(copy_envp) + 1));
	while ((*own_arg)[i])
	{
		if (ft_getenv(ft_find_name_var((*own_arg)[i]), copy_envp) != NULL)
		{
			new_envp[k++] = ft_strdup((*own_arg)[i]);
		}
		i++;
	}
	new_envp[k] = NULL;
	i = 0;
	while (copy_envp[i])
	{
		if (ft_getenv(ft_find_name_var(copy_envp[i]), new_envp) == NULL)
		{
			new_envp[k++] = ft_strdup(copy_envp[i]);
			new_envp[k] = NULL;
		}
		i++;
	}
	return (new_envp);
}

bool	ft_env(char **envp, char **copy_envp, t_mini *shell)
{
	int		i;
	char	**own_arg;

	i = 0;
	own_arg = ft_copy_envp_no_sort(envp);
	own_arg = ft_own_args(&own_arg, copy_envp, 0);
	if (shell->tab_pars[shell->tab_index + 1] != NULL
		&& shell->tab_pars[shell->tab_index + 1][0] != '|'
		&& shell->tab_pars[shell->tab_index + 1][0] != '>'
		&& shell->tab_pars[shell->tab_index + 1][0] != '<')
	{
		shell->status = 1;
		return (syntax_error(MANY_ARGS));
	}
	while (own_arg[i])
	{
		ft_printf("%s\n", own_arg[i]);
		i++;
	}
	return (true);
}
