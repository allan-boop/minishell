#include "../../include/minishell.h"

void	ft_add_new_var(t_mini **shell, char **envp, char *existing_var)
{
	int		i;
	char	*tmp;
	char	*just_name_var;

	i = 0;
	while (envp[i])
		i++;
	just_name_var = ft_find_name_var(existing_var);
	if (ft_check_last(just_name_var) == 1)
	{
		just_name_var[ft_strlen(just_name_var) - 1] = '\0';
		tmp = ft_strjoin_shell(just_name_var, "=");
		envp[i] = ft_strjoin(tmp, ft_find_value_var(existing_var));
	}
	else
		envp[i] = ft_strdup((*shell)->tab_pars[(*shell)->tab_index]);
	envp[i + 1] = NULL;
	ft_sort_envp(envp);
	(*shell)->team_envp = NULL;
	ft_create_list(envp, shell);
	return ;
}

void	ft_modify_var(t_mini *shell, char *existing_var, char **envp)
{
	char	*just_name_var;
	char	*just_name_var_plus;
	char	*new_var;
	char	*new_value;
	int		i;

	just_name_var = ft_find_name_var(existing_var);
	just_name_var_plus = ft_strdup(just_name_var);
	if (ft_check_last(just_name_var) == 1)
		just_name_var_plus[ft_strlen(just_name_var) - 1] = '\0';
	i = 0;
	while (ft_strcmp_shell(ft_find_name_var(envp[i]), just_name_var_plus) != 0)
		i++;
	if (ft_check_last(just_name_var) == 1)
		ft_check_plus(envp, just_name_var_plus, existing_var);
	else
	{
		new_value = ft_find_value_var(existing_var);
		new_var = ft_strjoin_shell(just_name_var, "=");
		new_var = ft_strjoin(new_var, new_value);
		envp[i] = new_var;
	}
	ft_sort_envp(envp);
	ft_create_list(envp, &shell);
}

static int	ft_already_exist(char *existing_var, char **envp)
{
	char	*just_name_var;
	int		i;

	just_name_var = ft_find_name_var(existing_var);
	i = 0;
	if (ft_check_last(just_name_var) == 1)
		just_name_var[ft_strlen(just_name_var) - 1] = '\0';
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
	if (ft_print_export_alone(shell) == true)
		return (true);
	shell->tab_index++;
	while (shell->tab_pars[shell->tab_index]
		&& (shell->tab_pars[shell->tab_index][0] != '|'
		|| shell->tab_pars[shell->tab_index][0] != '>'
		|| shell->tab_pars[shell->tab_index][0] != '<'))
	{
		ft_sort_envp(envp);
		if (ft_del_quotes(shell->tab_pars[shell->tab_index]) == 1)
			return (true);
		if (ft_current_arg(shell->tab_pars[shell->tab_index], envp) == 1)
		{
			syntax_error(INVALID_IDENTIFIER);
			return (true);
		}
		else if (ft_already_exist(shell->tab_pars[shell->tab_index], envp) == 0)
			ft_add_new_var(&shell, envp, shell->tab_pars[shell->tab_index]);
		else if (ft_already_exist(shell->tab_pars[shell->tab_index], envp) == 1)
			ft_modify_var(shell, shell->tab_pars[shell->tab_index], envp);
		shell->tab_index++;
	}
	return (true);
}
