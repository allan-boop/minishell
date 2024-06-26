#include "../../include/minishell.h"

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

static int	ft_find_exp( char *tab_pars, int j)
{
	while (tab_pars[j] != '\0'
		&& tab_pars[j] != '$'
		&& tab_pars[j] != ' '
		&& tab_pars[j] != 2
		&& tab_pars[j] != 3
		&& tab_pars[j] != 34
		&& tab_pars[j] != 39)
		j++;
	return (j);
}

char	*print_exp_var(char *tab_pars, char *str, char *n_str,
			t_int_utils *utils)
{
	int		k;
	bool	quote;

	quote = false;
	while (str)
	{
		while (tab_pars[(*utils).j] && tab_pars[(*utils).j] != '$')
		{
			if (tab_pars[(*utils).j] == 39)
			{
				n_str[((*utils).i)++] = tab_pars[((*utils).j++)];
				while (tab_pars[(*utils).j] != 39)
				{
					if (tab_pars[(*utils).j] == '$')
					{
						n_str[((*utils).i)++] = tab_pars[((*utils).j)];
						tab_pars[((*utils).j)++] = 'q';
						quote = true;
					}
					else
						n_str[((*utils).i)++] = tab_pars[((*utils).j)++];
				}
				n_str[((*utils).i)++] = tab_pars[((*utils).j)++];
			}
			else
				n_str[((*utils).i)++] = tab_pars[((*utils).j)++];
		}
		if (quote == false)
		{
			tab_pars[((*utils).j)++] = 'q';
			str = clean_var(str);
			(*utils).j = ft_find_exp(tab_pars, (*utils).j);
			k = 0;
			while ((*utils).envp[k])
			{
				if ((ft_strcmp("PWD", ft_find_name_var((*utils).envp[k])) == 0
						&& (*utils).env->pwd == false)
					|| (ft_strcmp("OLDPWD", ft_find_name_var((*utils).envp[k])) == 0
						&& (*utils).env->oldpwd == false)
					|| (ft_strcmp("HOME", ft_find_name_var((*utils).envp[k])) == 0
						&& (*utils).env->home == false)
					|| (ft_strcmp("SHLVL", ft_find_name_var((*utils).envp[k])) == 0
						&& (*utils).env->shlvl == false)
					|| (ft_strcmp("PATH", ft_find_name_var((*utils).envp[k])) == 0
						&& (*utils).env->path == false))
				{
					k++;
					continue ;
				}
				if (ft_strcmp(str + 1, ft_find_name_var((*utils).envp[k])) == 0)
				{
					n_str = ft_strjoin_shell(n_str,
							ft_getenv(str + 1, (*utils).envp));
					(*utils).i = ft_strlen(n_str);
				}
				k++;
			}
		}
		str = ft_strchr(tab_pars, '$');
	}
	return (n_str);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc_shell(ft_strlen(s1) + 2, sizeof(char));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*if_exp_var(t_mini *shell, t_env *env, int *i)
{
	char		*str;
	char		*n_str;
	t_int_utils	utils;

	utils.env = env;
	utils.i = 0;
	str = ft_strchr(shell->tab_pars[*i], '$');
	if (str)
	{
		n_str = ft_calloc_shell(ft_strlen(shell->tab_pars[*i])
				+ 1, sizeof(char));
		utils.j = 0;
		if (ft_is_in_quote(shell->tab_pars[*i], str) == 0)
		{
			utils.envp = env->copy_envp;
			n_str = print_exp_var(shell->tab_pars[*i], str, n_str, &utils);
		}
		while (shell->tab_pars[*i][utils.j])
		{
			n_str = ft_strjoin_char(n_str, shell->tab_pars[*i][utils.j]);
			(utils.i)++;
			(utils.j)++;
		}
		n_str[utils.i] = '\0';
		return (n_str);
	}
	return (shell->tab_pars[*i]);
}
