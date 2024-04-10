#include "../../include/minishell.h"

int	ft_is_in_quote(char *line, char *str)
{
	int		i;
	int		quote_count;

	quote_count = 0;
	i = 0;
	while (line[i] != str[0])
	{
		if (line[i] == 3)
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 0)
		return (0);
	return (1);
}
