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

static int	ft_find_exp(char *tab_pars, int j)
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

char	*print_exp_var(char *tab_pars, char *str, char *n_str,
			t_int_utils *utils)
{
	int		k;
	bool	quote;

	while (str)
	{
		quote = false;
		n_str = skip_bef_doll(tab_pars, utils, &quote, n_str);
		if (quote == false)
		{
			tab_pars[((*utils).j)++] = 'q';
			str = clean_var(str);
			(*utils).j = ft_find_exp(tab_pars, (*utils).j);
			k = 0;
			n_str = skip_env_var(str, n_str, utils, &k);
		}
		str = ft_strchr(tab_pars, '$');
	}
	return (n_str);
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
		n_str = ft_cat_str(shell, &utils, n_str, i);
		n_str[utils.i] = '\0';
		return (n_str);
	}
	return (shell->tab_pars[*i]);
}
