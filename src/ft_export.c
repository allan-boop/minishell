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

void	ft_print_export(void)
{

}

int	ft_already_exist(void)
{

}

void	ft_modify_var(void)
{

}

void	ft_export(char **args)
{
	if (args[1] == NULL)
	{
		ft_print_export();
		return ;
	}
	if (ft_already_exist() == 0)
		ft_add_new_var();
	else
		ft_modify_var();
}
