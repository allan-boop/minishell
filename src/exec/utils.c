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

static int	rep_quote(char **line, int *i, char **tmp, t_str_utils *utils)
{
	char	quote;

	if ((*line)[*i] == 34 || (*line)[*i] == 39)
	{
		quote = (*line)[*i];
		utils->start = ++(*i);
		while ((*line)[*i] && (*line)[*i] != quote)
		{
			if (!(*line)[*i])
				return (syntax_error(QUOTE_FAIL), 1);
			(*i)++;
		}
		utils->end = *i - 1;
		if (!*tmp)
			*tmp = ft_substr_shell((*line), utils->start,
					(utils->end - utils->start) + 1);
		else
			*tmp = ft_strjoin_shell(*tmp,
					ft_substr_shell((*line), utils->start,
						(utils->end - utils->start) + 1));
	}
	else
		*tmp = ft_strjoin_shell(*tmp, ft_substr_shell((*line), *i, 1));
	(*i)++;
	return (0);
}

static int	replace_quote(char **line, int *i, char **new_line)
{
	t_str_utils	utils;
	char		*tmp;
	int			ret;

	tmp = NULL;
	utils.start = 0;
	utils.end = 0;
	if ((*line)[*i] == 34 || (*line)[*i] == 39)
	{
		utils.start = *i;
		*new_line = ft_substr_shell(*line, 0, utils.start);
		while ((*line)[*i])
		{
			ret = rep_quote(line, i, &tmp, &utils);
			if (ret != 0)
				return (ret);
		}
		*new_line = ft_strjoin_shell(*new_line, tmp);
	}
	else
		(*i)++;
	return (0);
}

int	ft_replace_quote_export(char **line)
{
	char	*new_line;
	int		i;
	int		ret;

	if (!line)
		return (1);
	i = 0;
	new_line = NULL;
	while ((*line)[i])
	{
		ret = replace_quote(line, &i, &new_line);
		if (ret != 0)
			return (ret);
	}
	if (new_line)
		(*line) = ft_strdup_shell(new_line);
	return (0);
}
