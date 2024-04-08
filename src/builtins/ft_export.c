#include "../../include/minishell.h"

void	ft_add_new_var(t_mini **shell, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup((*shell)->tab_pars[(*shell)->tab_index]);
	envp[i + 1] = NULL;
	ft_sort_envp(envp);
	(*shell)->team_envp = NULL;
	ft_create_list(envp, shell);
	return ;
}

void	ft_print_export(t_mini *shell)
{
	t_envp	*tmp;

	tmp = shell->team_envp;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s\n", tmp->whole_var);
		tmp = tmp->next;
	}
}

void	ft_modify_var(t_mini *shell, char *existing_var, char **envp)
{
	char	*just_name_var;
	char	*new_var;
	char	*new_value;
	int		i;

	just_name_var = ft_find_name_var(existing_var);
	i = 0;
	while (ft_strcmp(ft_find_name_var(envp[i]), just_name_var) != 0)
		i++;
	new_value = ft_find_value_var(existing_var);
	new_var = ft_strjoin(just_name_var, "=");
	new_var = ft_strjoin(new_var, new_value);
	envp[i] = new_var;
	ft_sort_envp(envp);
	ft_create_list(envp, &shell);
}

static int	ft_already_exist(char *existing_var, char **envp)
{
	char	*just_name_var;
	int		i;
	int		j;

	just_name_var = ft_find_name_var(existing_var);
	j = ft_strlen(just_name_var);
	just_name_var[j + 1] = '\0';
	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(ft_find_name_var(envp[i]), just_name_var) == 0)
			return (1);
		i++;
	}
	return (0);
}

bool	ft_export(t_mini *shell, char **envp)
{
	shell->tab_index++;
	ft_sort_envp(envp);
	if (shell->tab_pars[shell->tab_index] == NULL)
	{
		ft_print_export(shell);
		return (true);
	}
	else if (ft_already_exist(shell->tab_pars[shell->tab_index], envp) == 0)
		ft_add_new_var(&shell, envp);
	else if (ft_already_exist(shell->tab_pars[shell->tab_index], envp) == 1)
		ft_modify_var(shell, shell->tab_pars[shell->tab_index], envp);
	return (false);
}
