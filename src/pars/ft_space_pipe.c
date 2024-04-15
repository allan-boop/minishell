#include "../../include/minishell.h"

static int	ft_len_space_pipe_two(int *i, char *line, size_t *len, char quote)
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
			syntax_error(PIPE_FAIL);
			return (-1);
		}
		if (*i > 0 && line[*i - 1] != ' ')
			(*len)++;
		if (line[*i + 1] != ' ')
			(*len)++;
	}
	return (0);
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
		if (ft_len_space_pipe_two(&i, line, &len, quote) == -1)
			return (-1);
		if (ft_len_space_redirect(&i, line, &len) == -1)
			return (-1);
		i++;
	}
	return (len);
}

static void	ft_space_pipe_two(int *i, int *j, char *line, char *tmp)
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

void	ft_space_pipe_one(int *i, int *j, char *line, char *tmp)
{
	char	quote;

	if (line[*i] == 34 || line[*i] == 39)
	{
		quote = line[*i];
		tmp[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != quote)
			tmp[(*j)++] = line[(*i)++];
	}
}

char	*ft_space_pipe(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_len_space_pipe(line) == -1)
		return (NULL);
	tmp = ft_alloc(ft_strlen(line) + ft_len_space_pipe(line) + 1);
	ft_bzero(tmp, ft_strlen(line) + ft_len_space_pipe(line) + 1);
	while (line[i])
	{
		ft_space_pipe_one(&i, &j, line, tmp);
		ft_space_pipe_two(&i, &j, line, tmp);
	}
	ft_del_alloc(line);
	return (tmp);
}
