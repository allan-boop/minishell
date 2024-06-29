/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_exp_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:32:38 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:39 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_env_var(char *str, char *n_str, t_int_utils *utils, int *k)
{
	while ((*utils).envp[*k])
	{
		if ((ft_strcmp("PWD", ft_find_name_var((*utils).envp[*k])) == 0
				&& (*utils).env->pwd == false)
			|| (ft_strcmp("OLDPWD", ft_find_name_var((*utils).envp[*k])) == 0
				&& (*utils).env->oldpwd == false)
			|| (ft_strcmp("HOME", ft_find_name_var((*utils).envp[*k])) == 0
				&& (*utils).env->home == false)
			|| (ft_strcmp("SHLVL", ft_find_name_var((*utils).envp[*k])) == 0
				&& (*utils).env->shlvl == false)
			|| (ft_strcmp("PATH", ft_find_name_var((*utils).envp[*k])) == 0
				&& (*utils).env->path == false))
		{
			(*k)++;
			continue ;
		}
		if (ft_strcmp(str + 1, ft_find_name_var((*utils).envp[*k])) == 0)
		{
			n_str = ft_strjoin_shell(n_str,
					ft_getenv(str + 1, (*utils).envp));
			(*utils).i = ft_strlen(n_str);
		}
		(*k)++;
	}
	return (n_str);
}

char	*skip_doll_betw_q(char *tab_pars, char *n_str,
							t_int_utils *utils, bool *quote)
{
	while (tab_pars[(*utils).j] != 39)
	{
		if (tab_pars[(*utils).j] == '$')
		{
			n_str = ft_strjoin_char(n_str, tab_pars[(*utils).j]);
			(*utils).i++;
			tab_pars[((*utils).j)++] = 'q';
			*quote = true;
		}
		else
		{
			n_str = ft_strjoin_char(n_str, tab_pars[(*utils).j]);
			(*utils).i++;
			(*utils).j++;
		}
	}
	return (n_str);
}

char	*skip_bef_doll( char *tab_pars, t_int_utils *utils,
						bool *quote, char *n_str)
{
	while (tab_pars[(*utils).j] && tab_pars[(*utils).j] != '$')
	{
		if (tab_pars[(*utils).j] == 39)
		{
			n_str = ft_strjoin_char(n_str, tab_pars[(*utils).j]);
			(*utils).i++;
			(*utils).j++;
			n_str = skip_doll_betw_q(tab_pars, n_str, utils, quote);
			n_str = ft_strjoin_char(n_str, tab_pars[(*utils).j]);
			(*utils).i++;
			(*utils).j++;
		}
		else
		{
			n_str = ft_strjoin_char(n_str, tab_pars[(*utils).j]);
			(*utils).i++;
			(*utils).j++;
		}
	}
	return (n_str);
}

char	*ft_cat_str(t_mini *shell, t_int_utils *utils, char *n_str, int *i)
{
	while (shell->tab_pars[*i][(*utils).j])
	{
		n_str = ft_strjoin_char(n_str, shell->tab_pars[*i][(*utils).j]);
		((*utils).i)++;
		((*utils).j)++;
	}
	return (n_str);
}
