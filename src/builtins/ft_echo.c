#include "../../include/minishell.h"

char	*clean_vard(char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != 2 && str[i] != 3 && str[i] != 34 && str[i] != 39)
		i++;
	var = ft_alloc(i + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != 2 && str[i] != 3 && str[i] != 34 && str[i] != 39)
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = '\0';
	return (var);
}

bool	ft_n_option(bool *n_option, bool is_n_option, t_mini *shell, int *i)
{
	int	j;

	while (is_n_option == true)
	{
		j = 0;
		if (shell->tab_pars[*i][j] == '-'
			&& shell->tab_pars[*i][j + 1] == 'n')
		{
			j++;
			while (shell->tab_pars[*i][j] == 'n')
				j++;
			if (shell->tab_pars[*i][j] == '\0')
			{
				*n_option = true;
				(*i)++;
			}
			else
				is_n_option = false;
		}
		else
			is_n_option = false;
	}
	return (false);
}

void	print_exp_vard(char *tab_pars, char **envp, int *j, char *str)
{
	int		k;

	while (str)
	{
		while (tab_pars[*j] != '$')
			ft_printf("%c", tab_pars[(*j)++], 1);
		tab_pars[(*j)++] = 'q';
		str = clean_vard(str);
		while (tab_pars[*j] != '\0'
			&& tab_pars[*j] != '$'
			&& tab_pars[*j] != ' '
			&& tab_pars[*j] != 2
			&& tab_pars[*j] != 3
			&& tab_pars[*j] != 34
			&& tab_pars[*j] != 39)
			(*j)++;
		k = 0;
		while (envp[k])
		{
			if (ft_strcmp(str + 1, ft_find_name_var(envp[k])) == 0)
				ft_putstr_fd(ft_getenv(str + 1, envp), 1);
			k++;
		}
		str = ft_strchr(tab_pars, '$');
	}	
}

void	if_exp_vard(t_mini *shell, char **envp, int *i)
{
	int		j;
	char	*str;

	str = ft_strchr(shell->tab_pars[*i], '$');
	if (str)
	{
		j = 0;
		if (ft_is_in_quote(shell->tab_pars[*i], str) == 0)
			print_exp_vard(shell->tab_pars[*i], envp, &j, str);
		while (shell->tab_pars[*i][j])
			ft_printf("%c", shell->tab_pars[*i][j++], 1);
		if (shell->tab_pars[*i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	else
	{
		ft_putstr_fd(shell->tab_pars[*i], 1);
		if (shell->tab_pars[*i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}	
}

bool	ft_echo(t_mini *shell, char **envp)
{
	int		i;
	bool	n_option;
	bool	is_n_option;

	i = 1;
	n_option = false;
	is_n_option = true;
	shell->status = 0;
	while (shell->tab_pars[i] != NULL)
	{
		is_n_option = ft_n_option(&n_option, is_n_option, shell, &i);
		ft_replace_space_in_str(shell->tab_pars[i], true);
		if_exp_vard(shell, envp, &i);
		i++;
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	return (true);
}
