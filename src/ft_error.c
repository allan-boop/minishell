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