#include "../../include/minishell.h"

static char	**ft_own_args(char ***own_arg, char **envp, char **copy_envp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (envp[i] && copy_envp[k])
	{
		if (ft_strcmp_shell(envp[i], copy_envp[k]) != 0)
		{
			(*own_arg)[j] = ft_strdup_shell(envp[i]);
			j++;
			i++;
			k = 0;
		}
		else
			k++;
	}
	(*own_arg)[j] = NULL;
	return (*own_arg);
}

bool	ft_env(char **envp, char **copy_envp, t_mini *shell)
{
	int		i;
	char	**own_arg;

	i = 0;
	own_arg = ft_alloc(sizeof(char *) * (ft_tab_len(envp) + 1));
	own_arg = ft_own_args(&own_arg, envp, copy_envp);
	if (shell->tab_pars[shell->tab_index + 1] != NULL
		&& shell->tab_pars[shell->tab_index + 1][0] != '|'
		&& shell->tab_pars[shell->tab_index + 1][0] != '>'
		&& shell->tab_pars[shell->tab_index + 1][0] != '<')
	{
		shell->status = 1;
		return (syntax_error(MANY_ARGS));
	}
	while (copy_envp[i])
	{
		ft_printf("%s\n", copy_envp[i]);
		i++;
	}
	while (own_arg[i])
	{
		ft_printf("%s\n", own_arg[i]);
		i++;
	}
	return (true);
}
