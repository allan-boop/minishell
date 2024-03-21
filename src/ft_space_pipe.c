#include "../include/minishell.h"

int	ft_len_space_pipe(char *line)
{
	int		i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			while (line[i] != quote)
				i++;
		}
		if (line[i] == '|')
		{
			if (line[i - 1] != ' ')
				len++;
			if (line[i + 1] != ' ')
				len++;
		}
		i++;
	}
	return (len);
}

void	ft_space_pipe_two(int *i, int *j, char *line, char *tmp)
{
	if (line[*i] == '|')
	{
		if (line[*i - 1] != ' ')
		{
			tmp[*j] = ' ';
			(*j)++;
			tmp[*j] = '|';
		}
		if (line[*i + 1] != ' ')
		{
			(*j)++;
			tmp[*j] = ' ';
			(*i)++;
			(*j)++;
		}
	}
	tmp[*j] = line[*i];
	(*j)++;
	if (line[*i])
		(*i)++;
}

char	*ft_space_pipe(char *line)
{
	char	*tmp;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_alloc(ft_strlen(line) + ft_len_space_pipe(line) + 1);
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			tmp[j] = line[i];
			i++;
			while (line[i] != quote)
				tmp[j] = line[i++];
		}
		ft_space_pipe_two(&i, &j, line, tmp);
	}
	tmp[j] = '\0';
	ft_del_alloc(line);
	return (tmp);
}
