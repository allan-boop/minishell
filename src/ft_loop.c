#include "../include/minishell.h"

char	*clean_var(char *str)
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

char	*print_exp_var(char *tab_pars, char **envp, int *j, char *str, char *n_str, int *l)
{
	int		k;

	while (str)
	{
		while (tab_pars[*j] != '$')
			n_str[(*l)++] = tab_pars[(*j)++];
		tab_pars[(*j)++] = 'q';
		str = clean_var(str);
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
			{
				n_str = ft_strjoin_shell(n_str, ft_getenv(str + 1, envp));
				*l = ft_strlen(n_str);
			}
			k++;
		}
		str = ft_strchr(tab_pars, '$');
	}
	return (n_str);
}

char	*if_exp_var(t_mini *shell, char **envp, int *i)
{
	int		j;
	char	*str;
	char	*n_str;
	int		k;

	k = 0;
	str = ft_strchr(shell->tab_pars[*i], '$');
	if (str)
	{
		n_str = ft_calloc(ft_strlen(shell->tab_pars[*i]) + 1, sizeof(char));
		j = 0;
		if (ft_is_in_quote(shell->tab_pars[*i], str) == 0)
			n_str = print_exp_var(shell->tab_pars[*i], envp, &j, str, n_str, &k);
		while (shell->tab_pars[*i][j])
			n_str[k++] = shell->tab_pars[*i][j++];
		if (shell->tab_pars[*i + 1] != NULL)
			n_str[k++] = ' ';
		n_str[k] = '\0';
		return (n_str);
	}
	return (shell->tab_pars[*i]);
}


void	prompt_treatment(char *line, t_mini *shell,
	char **envp, char ***copy_envp)
{
	int				error;

	if (line[0] != '\0')
	{
		error = ft_parsing(shell, line, *copy_envp);
		if (error == 0)
		{
			shell->list = create_list(shell);
			add_history(line);
			ft_copy_envp(*copy_envp, shell);
			if (shell->list->error_parsing == false)
				ft_execution(shell, envp, copy_envp);
		}
	}
}

void	ft_loop(char **envp)
{
	char			*line;
	t_mini			*shell;
	char			**copy_envp;

	ft_signal();
	copy_envp = ft_copy_envp_no_sort(envp);
	while (1)
	{
		shell = ft_alloc(sizeof(t_mini));
		shell->og_stdin = dup(STDIN_FILENO);
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_printf("\n");
			exit(0);
		}
		prompt_treatment(line, shell, envp, &copy_envp);
		free(line);
		ft_del_all();
	}
	free(copy_envp);
}
