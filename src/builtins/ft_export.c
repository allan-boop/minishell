#include "../../include/minishell.h"

void	ft_add_new_var_two(char ***new_tab, t_mini **shell, int i)
{
	(*new_tab)[i + 1] = NULL;
	(*new_tab) = ft_sort_envp(*new_tab);
	(*shell)->team_envp = NULL;
	ft_create_list(new_tab, shell);
}

void	ft_add_new_var(t_mini **shell, char ***copy_envp, char *existing_var)
{
	int		i;
	char	*tmp;
	char	**new_tab;
	char	*just_name_var;

	i = -1;
	new_tab = malloc(sizeof(char *) * (ft_tab_len(*copy_envp) + 2));
	while ((*copy_envp)[++i])
		new_tab[i] = ft_strdup((*copy_envp)[i]);
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
	i = -1;
	while ((*copy_envp)[++i])
		free((*copy_envp)[i]);
	free(*copy_envp);
	*copy_envp = new_tab;
	return ;
}

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

static int	ft_export_core(char ***copy_envp, t_mini *shell,
	char *just_name_var)
{
	if (ft_del_quotes(&shell->tab_pars[shell->tab_index]) == 1)
		return (true);
	if (ft_current_arg(shell->tab_pars[shell->tab_index], *copy_envp) == 1)
	{
		shell->status = 1;
		syntax_error(INVALID_IDENTIFIER);
	}
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			copy_envp, shell) == 2)
		return (shell->tab_index++, 1);
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			copy_envp, shell) == 0)
		ft_add_new_var(&shell,
			copy_envp, shell->tab_pars[shell->tab_index]);
	else if (ft_already_exist(shell->tab_pars[shell->tab_index],
			copy_envp, shell) == 1)
	{
		just_name_var = ft_find_name_var(shell->tab_pars[shell->tab_index]);
		ft_modify_var(shell, shell->tab_pars[shell->tab_index],
			copy_envp, just_name_var);
	}
	shell->tab_index++;
	return (0);
}

bool	ft_export(t_mini *shell, char ***copy_envp)
{
	char	*just_name_var;

	just_name_var = NULL;
	if (ft_print_export_alone(shell) == true)
		return (true);
	shell->tab_index++;
	shell->status = 0;
	while (shell->tab_pars[shell->tab_index]
		&& shell->tab_pars[shell->tab_index][0] != '|'
		&& shell->tab_pars[shell->tab_index][0] != '>'
		&& shell->tab_pars[shell->tab_index][0] != '<')
	{
		ft_sort_envp(*copy_envp);
		if (ft_export_core(copy_envp, shell, just_name_var) == 1)
			continue ;
	}
	return (true);
}
