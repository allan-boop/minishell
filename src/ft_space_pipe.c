#include "../include/minishell.h"

static void	ft_len_space_pipe_two(int *i, char *line, size_t *len, char quote)
{
	if (line[*i] == 34 || line[*i] == 39)
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
	}
	if (line[*i] == '|')
	{
		if (line[*i + 1] == '|')
		{
			printf("Error bad pipe.\n");
			exit(1);
		}
		if (*i > 0 && line[*i - 1] != ' ')
			(*len)++;
		if (line[*i + 1] != ' ')
			(*len)++;
	}
}

int	ft_len_space_pipe(char *line)
{
	int		i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (line[i])
	{
		ft_len_space_pipe_two(&i, line, &len, quote);
		ft_len_space_redirect(&i, line, &len);
		i++;
	}
	return (len);
}

void	ft_space_pipe_two(int *i, int *j, char *line, char *tmp)
{
	if (line[*i] == '|')
	{
		if (*i > 0 && line[*i - 1] != ' ')
		{
			tmp[*j] = ' ';
			(*j)++;
		}
		tmp[*j] = '|';
		(*j)++;
		(*i)++;
		if (line[*i] != ' ')
		{
			tmp[*j] = ' ';
			(*j)++;
		}
	}
	if (line[*i] == '>' || line[*i] == '<')
		ft_space_redirect(i, j, line, tmp);
	else
	{
		tmp[*j] = line[*i];
		(*j)++;
		if (line[*i])
			(*i)++;
	}
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
	ft_bzero(tmp, ft_strlen(line) + ft_len_space_pipe(line) + 1);
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			tmp[j] = line[i];
			i++;
			j++;
			while (line[i] && line[i] != quote)
				tmp[j++] = line[i++];
		}
		ft_space_pipe_two(&i, &j, line, tmp);
	}
	printf("//%d\n", tmp[j - 1]);
	ft_del_alloc(line);
	return (tmp);
}
