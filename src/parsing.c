#include "../include/minishell.h"

static void	ft_replace_space(char **line)
{
	int		i;
	char	quote;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == 34 || (*line)[i] == 39)
		{
			quote = (*line)[i];
			if ((*line)[i + 1])
				i++;
			while ((*line)[i] && (*line)[i] != quote)
			{
				if ((*line)[i] == ' ')
					(*line)[i] = 1;
				i++;
			}
		}
		i++;
	}
}

static char	**ft_put_space_between(char **tab_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab_line[i])
	{
		while (tab_line[i][j])
		{
			if (tab_line[i][j] == 1)
				tab_line[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
	return (tab_line);
}

void	ft_parsing(t_mini *shell, char *line)
{
	char	**tab_line;

	ft_replace_space(&line);
	tab_line = ft_split_shell(line, ' ');
	tab_line = ft_put_space_between(tab_line);
	(void)tab_line;
	(void)shell;
}
