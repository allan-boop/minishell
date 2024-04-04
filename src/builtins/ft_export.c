#include "../../include/minishell.h"

/*
Si export sans argument, afficher toutes les variables d'environnement.
Si variable_inexistante == true:
	alors creer variable.
Autrement:
	modifier variable.
*/

// void	ft_add_new_var(t_mini **shell)
// {
// 	t_envp	*new;
// 	t_envp	*tmp;
// 	int		i;
// 	int		j;

// 	new = ft_lstnew_envp((*shell)->tab_pars[(*shell)->tab_index]);
// 	tmp = (*shell)->team_envp;
// 	i = 0;
// 	j = 0;
// 	while (tmp->next && ft_strcmp(tmp->var, ((*shell)->tab_pars[(*shell)->tab_index])) < 0)
// 	{
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	tmp = (*shell)->team_envp;
// 	while (j < i)
// 	{
// 		tmp = tmp->next;
// 		j++;
// 	}
// 	new->next = tmp->next;
// 	tmp->next = new;
// }

void	ft_add_new_var(t_mini **shell, char **envp)
{
	int		i;
	int		len;
	t_envp	*new;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup((*shell)->tab_pars[(*shell)->tab_index]);
	envp[i + 1] = NULL;
	ft_sort_envp(envp);
	len = ft_tab_len(envp);
	(*shell)->team_envp = NULL;
	i = 0;
	while (i < len - 1)
	{
		new = ft_lstnew_envp(envp[i]);
		ft_lstadd_back_envp(shell, new);
		i++;
	}
	return ;
}

void	ft_print_export(t_mini *shell)
{
	t_envp	*tmp;

	tmp = shell->team_envp;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

// void	ft_modify_var(void)
// {

// }

static int	ft_already_exist(t_mini shell)
{
	while (shell.team_envp && shell.team_envp->var)
	{
		if (ft_strnstr(shell.team_envp->var, shell.tab_pars[shell.tab_index],
				ft_strlen(shell.team_envp->var) == 0))
			return (1);
		shell.team_envp = shell.team_envp->next;
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
	else if (ft_already_exist(*shell) == 0)
		ft_add_new_var(&shell, envp);
	// else
	// 	ft_modify_var();
	return (false);
}
