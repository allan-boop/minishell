#include "../include/minishell.h"

/*
Si export sans argument, afficher toutes les variables d'environnement.
Si variable_inexistante == true:
	alors creer variable.
Autrement:
	modifier variable.
*/

void	ft_add_new_var(void)
{

}

void	find_minimal_letter(t_mini *shell)
{

}

char	**ft_sort_envp(t_mini *shell)
{
	char	*first;
	int		i;

	i = 0;
	first = shell->team_envp->var;
	while (shell->team_envp->next)
	{
		if ((int)shell->team_envp->var[i] > (int)shell->team_envp->next->var[i])
		{

		}
	}
}

void	ft_print_export(t_mini *shell)
{
	while (shell->team_envp->next)
	{
		printf("declare -x ");
		printf("%s\n", shell->team_envp->var);
		shell->team_envp = shell->team_envp->next;
	}
	if (shell->team_envp->var)
		return ;
	while (shell->team_envp->next)
	{
		printf("declare -x ");
		printf("%s\n", shell->team_envp->var);
		shell->team_envp = shell->team_envp->next;
	}
}

int	ft_already_exist(void)
{

}

void	ft_modify_var(void)
{

}

void	ft_export(char **args, t_mini *shell)
{
	ft_sort_envp(shell);
	if (args[1] == NULL)
	{
		ft_print_export(shell);
		return ;
	}
	else if (ft_already_exist() == 0)
		ft_add_new_var();
	else
		ft_modify_var();
}
