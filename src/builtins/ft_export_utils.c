#include "../../include/minishell.h"

void	ft_print_export(t_mini *shell)
{
	t_envp	*tmp;

	tmp = shell->team_envp;
	while (tmp)
	{
		if (tmp->value[0] == 0)
			printf("declare -x %s\n", tmp->var);
		else
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

bool	ft_print_export_alone(t_mini *shell)
{
	if (ft_strcmp_shell(shell->tab_pars[shell->tab_index], "export") == 0
		&& (shell->tab_pars[1] == NULL
			|| shell->tab_pars[1][0] == '#'
		|| shell->tab_pars[1][0] == ';'))
	{
		ft_print_export(shell);
		return (true);
	}
	return (false);
}
