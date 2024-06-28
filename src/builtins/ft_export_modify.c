#include "../../include/minishell.h"

static void	ft_modify_var_in(char **new_value, char *existing_var,
	char *just_name_var, char **new_var)
{
	*new_value = ft_find_value_var(existing_var);
	*new_var = ft_strjoin_shell(just_name_var, "=");
	*new_var = ft_strjoin(*new_var, *new_value);
}

void	ft_modify_var(t_mini *shell, char *existing_var,
	t_env *env, char *just_name_var)
{
	char	*just_name_var_plus;
	char	*new_var;
	char	*new_value;
	int		i;

	yes_unset_env(just_name_var, env);
	just_name_var_plus = ft_strdup_shell(just_name_var);
	if (ft_check_last(just_name_var, &shell) == 2)
		return ;
	if (ft_check_last(just_name_var, &shell) == 1)
		just_name_var_plus[ft_strlen(just_name_var) - 1] = '\0';
	i = 0;
	while (ft_strcmp_shell(ft_find_name_var(((*env).copy_envp)[i]),
		just_name_var_plus) != 0)
		i++;
	if (ft_check_last(just_name_var, &shell) == 1)
		ft_check_plus(((*env).copy_envp), just_name_var_plus, existing_var);
	else
	{
		ft_modify_var_in(&new_value, existing_var, just_name_var, &new_var);
		free((*env).copy_envp[i]);
		(*env).copy_envp[i] = new_var;
	}
	ft_create_list(&((*env).copy_envp), &shell);
	return ;
}
