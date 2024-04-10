#include "../../include/minishell.h"

static void	ft_replace_quote(char *line, int i)
{
	if (line[i] == 34)
		line[i] = 2;
	else if (line[i] == 39)
		line[i] = 3;
}

void	ft_replace_space_in_str(char *line, bool only_quote)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			ft_replace_quote(line, i);
			if (line[i + 1])
				i++;
			while (line[i] && line[i] != quote)
			{
				if (only_quote == false && line[i] == ' ')
					line[i] = 1;
				i++;
			}
			if (line[i] && line[i] == quote && line[i] == 34)
				line[i] = 2;
			else if (line[i] && line[i] == quote && line[i] == 39)
				line[i] = 3;
		}
		i++;
	}
}