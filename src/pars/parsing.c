#include "../../include/minishell.h"

static void	ft_replace_quote(char **line, int i)
{
	if ((*line)[i] == 34)
		(*line)[i] = 2;
	else if ((*line)[i] == 39)
		(*line)[i] = 3;
}

void	ft_replace_space(char **line)
{
	int		i;
	char	quote;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == 34 || (*line)[i] == 39)
		{
			quote = (*line)[i];
			ft_replace_quote(line, i);
			if ((*line)[i + 1])
				i++;
			while ((*line)[i] && (*line)[i] != quote)
			{
				if ((*line)[i] == ' ')
					(*line)[i] = 1;
				i++;
			}
			if ((*line)[i] && (*line)[i] == quote && (*line)[i] == 34)
				(*line)[i] = 2;
			else if ((*line)[i] && (*line)[i] == quote && (*line)[i] == 39)
				(*line)[i] = 3;
		}
		i++;
	}
}

char	**ft_put_space_between(char **tab_line)
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
			else if (tab_line[i][j] == 2)
				tab_line[i][j] = 34;
			else if (tab_line[i][j] == 3)
				tab_line[i][j] = 39;
			j++;
		}
		j = 0;
		i++;
	}
	return (tab_line);
}

int	ft_parsing(t_mini *shell, char *line, char **envp)
{
	int		i;

	if (ft_check_quote(line) == 1)
		return (1);
	line = ft_space_pipe(line);
	if (!line)
		return (1);
	ft_replace_space(&line);
	shell->tab_pars = ft_split_shell(line, ' ');
	shell->tab_pars = ft_put_space_between(shell->tab_pars);
	i = 0;
	while (shell->tab_pars[i])
	{
		if (ft_strcmp_shell(shell->tab_pars[i], "$?") == 0)
			shell->tab_pars[i] = ft_replace_doll(shell->tab_pars[i],
					ft_itoa_shell(shell->status));
		shell->tab_pars[i] = if_exp_var(shell, envp, &i);
		i++;
	}
	if (shell->tab_pars[0][0] == '|')
		return (1);
	ft_list_cmd(&shell);
	return (0);
}
