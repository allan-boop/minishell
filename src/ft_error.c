#include "../include/minishell.h"

void	ft_nb_args(int argc)
{
	if (argc != 1)
	{
		ft_printf(MANY_ARGS);
		exit (1);
	}
}

void	ft_check_quote(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
			{
				printf("Quote error.\n");
				exit (1);
			}
		}
		i++;
	}
}

void	ft_error_parsing(t_list_struct	*list)
{
	while (list)
	{
		printf("test\n");
		if (list->is_redir == true && list->next == NULL)
		{
			printf("Error redirection.\n");
			exit (1);
		}
		if (list->is_redir == true && list->next->is_redir == true)
		{
			printf("Error redirection.\n");
			exit (1);
		}
		if (list->is_redir == true && list->next->is_operator == true)
		{
			printf("Error redirection.\n");
			exit (1);
		}
		list = list->next;
	}
}
