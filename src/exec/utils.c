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

static void	ft_del_quote_export(char *line, int i)
{
	int	j;

	j = i;
	if (line[j] == 34)
	{
		while (line[j])
		{
			line[j] = line[j + 1];
			j++;
		}
		line[j] = '\0';
	}
	if (line[j] == 39)
	{
		while (line[j])
		{
			line[j] = line[j + 1];
			j++;
		}
		line[j] = '\0';
	}

}

void	ft_replace_quote_export(char *line, bool only_quote)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			ft_del_quote_export(line, i);
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
