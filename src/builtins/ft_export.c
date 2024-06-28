#include "../../include/minishell.h"

static int	ft_already_exist(char *existing_var,
	char ***copy_envp, t_mini *shell)
{
	char	*just_name_var;
	int		i;

	just_name_var = ft_find_name_var(existing_var);
	i = 0;
	if (ft_check_last(just_name_var, &shell) == 2)
		return (2);
	if (ft_check_last(just_name_var, &shell) == 1)
		just_name_var[ft_strlen(just_name_var) - 1] = '\0';
	while ((*copy_envp)[i])
	{
		if (ft_strcmp(ft_find_name_var((*copy_envp)[i]), just_name_var) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_export_core(t_env *env, t_mini *shell,
	char *just_name_var)
{
	if (ft_del_quotes(&shell->tab_pars[shell->tab_index]) == 1)
		return (true);
	if (ft_current_arg(shell->tab_pars[shell->tab_index]) == 1)
	{
		shell->status = 1;
		syntax_error(INVALID_IDENTIFIER);
	}
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			&((*env).copy_envp), shell) == 2)
		return (shell->tab_index++, 1);
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			&((*env).copy_envp), shell) == 0)
		ft_add_new_var(&shell, env,
			shell->tab_pars[shell->tab_index]);
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			&((*env).copy_envp), shell) == 1)
	{
		just_name_var = ft_find_name_var(shell->tab_pars[shell->tab_index]);
		ft_modify_var(shell, shell->tab_pars[shell->tab_index],
			env, just_name_var);
	}
	shell->tab_index++;
	return (0);
}

bool	ft_export(t_mini *shell, t_env *env)
{
	char	*just_name_var;

	just_name_var = NULL;
	if (ft_print_export_alone(shell, env) == true)
		return (true);
	shell->tab_index++;
	shell->status = 0;
	while (shell->tab_pars[shell->tab_index]
		&& shell->tab_pars[shell->tab_index][0] != '|'
		&& shell->tab_pars[shell->tab_index][0] != '>'
		&& shell->tab_pars[shell->tab_index][0] != '<')
	{
		ft_sort_envp(env);
		if (ft_export_core(env, shell, just_name_var) == 1)
			continue ;
	}
	return (true);
}
