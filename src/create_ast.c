#include "../include/minishell.h"

void	create_ast(t_mini *shell)
{
	ft_give_token();
	first_node();
	children_node();
}
