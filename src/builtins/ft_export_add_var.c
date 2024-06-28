#include "../../include/minishell.h"

static void	ft_add_new_var_two(char ***new_tab, t_mini **shell, int i)
{
	(*new_tab)[i + 1] = NULL;
	(*new_tab) = ft_sort_envp_char(*new_tab);
	(*shell)->team_envp = NULL;
	ft_create_list(new_tab, shell);
}

void	ft_add_new_var_clean(t_env *env, char **new_tab)
{
	int	i;

	i = -1;
	while ((*env).copy_envp[++i])
		free((*env).copy_envp[i]);
	free((*env).copy_envp);
	(*env).copy_envp = NULL;
	(*env).copy_envp = new_tab;
}

void	ft_add_new_var(t_mini **shell, t_env *env, char *existing_var)
{
	int		i;
	char	*tmp;
	char	**new_tab;
	char	*just_name_var;

	i = -1;
	new_tab = malloc(sizeof(char *) * (ft_tab_len((*env).copy_envp) + 2));
	while ((*env).copy_envp[++i])
		new_tab[i] = ft_strdup((*env).copy_envp[i]);
	just_name_var = ft_find_name_var(existing_var);
	if (ft_check_last(just_name_var, shell) == 1)
	{
		just_name_var[ft_strlen(just_name_var) - 1] = '\0';
		tmp = ft_strjoin_shell(just_name_var, "=");
		new_tab[i] = ft_strjoin(tmp, ft_find_value_var(existing_var));
	}
	else
		new_tab[i] = ft_strdup((*shell)->tab_pars[(*shell)->tab_index]);
	ft_add_new_var_two(&new_tab, shell, i);
	ft_add_new_var_clean(env, new_tab);
	return ;
}
