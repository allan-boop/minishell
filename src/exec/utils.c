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

int	ft_replace_quote_export(char **line)
{
	char	*new_line;
	char	*tmp;
	char	quote;
	int		i;
	size_t	start;
	size_t	end;

	if (!line)
		return (1);
	quote = 0;
	start = 0;
	end = 0;
	i = 0;
	new_line = NULL;
	printf("line = %s\n", *line);
	while ((*line)[i])
	{
		if ((*line)[i] == 34 || (*line)[i] == 39)
		{
			quote = (*line)[i];
			start = ++i;
			while ((*line)[i] && (*line)[i] != quote)
			{
				if (!(*line)[i])
					return (syntax_error(QUOTE_FAIL),1);
				i++;
			}
			end = i - 1;
		}
		if (start != 0 && end != 0)
		{
			new_line = ft_substr_shell(*line, 0, start - 1);
			printf("new_line = %s\n", new_line);
			tmp = ft_substr_shell((*line), start, (end - start) + 1);
			new_line = ft_strjoin_shell(new_line, tmp);
			printf("new_line = %s\n", new_line);
			tmp = ft_substr_shell((*line), end + 2, ft_strlen((*line)) - end);
			/*while ((*line)[i])
			{
				printf("1");
				if ((*line)[i] == 34 || (*line)[i] == 39)
				{
					printf("2");
					quote = (*line)[i];
					start = ++i;
					while ((*line)[i] && (*line)[i] != quote)
					{
						printf("3");
						if (!(*line)[i])
							return (syntax_error(QUOTE_FAIL),1);
						i++;
					}
					end = i - 1;
				}
				new_line = ft_strjoin_shell(new_line, ft_substr_shell((*line), start, (end - start) + 1));
				printf("4");
				i++;
			}*/
			new_line = ft_strjoin_shell(new_line, tmp);
			i = ft_strlen(new_line) + 2;
			start = i;
			end = 0;
		}
		i++;
	}
	if (new_line)
		(*line) = ft_strdup_shell(new_line);
	return (0);
}
