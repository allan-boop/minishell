#include "../../include/minishell.h"

bool	ft_exit(void)
{
	ft_printf("exit\n");
	ft_del_all();
	exit(0);
	return (true);
}
