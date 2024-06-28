#include "../../include/minishell.h"

static int	ft_nb_pipe_cmd(t_mini *shell)
{
	int	i;
	int	nb_pipe;

	nb_pipe = 0;
	i = 0;
	while (shell->tab_pars && shell->tab_pars[i])
	{
		if (shell->tab_pars[i][0] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

static char	*ft_list_cmd_two(t_mini **shell, char *tmp, int *i)
{
	tmp = ft_strdup_shell((*shell)->tab_pars[*i]);
	(*i)++;
	while ((*shell)->tab_pars[*i] && (*shell)->tab_pars[*i][0] != '|')
	{
		if ((*shell)->tab_pars[*i][0] == '<'
			|| (*shell)->tab_pars[*i][0] == '>')
		{
			(*i)++;
			if ((*shell)->tab_pars[*i] && (*shell)->tab_pars[*i][0] != '|')
				(*i)++;
		}
		else
		{
			tmp = ft_strjoin_shell(tmp, " ");
			tmp = ft_strjoin_shell(tmp, (*shell)->tab_pars[*i]);
			(*i)++;
		}
	}
	return (tmp);
}

void	ft_list_cmd(t_mini **shell)
{
	char	*tmp;
	int		i;
	int		j;
	int		nb_pipe;

	i = 0;
	j = 0;
	nb_pipe = ft_nb_pipe_cmd(*shell);
	if ((*shell)->tab_pars[i][0] != '<' && (*shell)->tab_pars[i][0] != '>')
		nb_pipe++;
	if (nb_pipe == 0)
		return ;
	(*shell)->tab_cmd = ft_alloc(sizeof(char **) * (nb_pipe + 1));
	while (j < nb_pipe && (*shell)->tab_pars[i])
	{
		tmp = NULL;
		if ((*shell)->tab_pars[i] && (*shell)->tab_pars[i + 1]
			&& (*shell)->tab_pars[i][0] == '|')
			i++;
		tmp = ft_list_cmd_two(shell, tmp, &i);
		if (tmp)
			(*shell)->tab_cmd[j++] = ft_strdup_shell(tmp);
		i++;
	}
	(*shell)->tab_cmd[j] = NULL;
}
