/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:48 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 16:22:28 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_replace_value_var(char *own_arg, t_env *env)
{
	int		i;
	char	*name_var_env;
	char	*name_var_own;

	i = 0;
	while ((*env).copy_envp[i] && own_arg)
	{
		name_var_env = ft_find_name_var((*env).copy_envp[i]);
		name_var_own = ft_find_name_var(own_arg);
		if (ft_strcmp(name_var_env, name_var_own) == 0)
		{
			printf("%s\n", (*env).copy_envp[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_env_in_in(int *i, char **own_arg, t_env *env)
{
	if (ft_replace_value_var(own_arg[(*i)], env) == 1)
	{
		(*i)++;
		return ;
	}
	ft_printf("%s\n", own_arg[(*i)]);
	(*i)++;
}

static void	ft_env_in(t_env *env, char **own_arg, int *i)
{
	while (own_arg[(*i)])
	{
		if ((ft_strcmp(ft_find_name_var(own_arg[(*i)]),
					"OLDPWD") == 0 && (*env).oldpwd == false)
			|| (ft_strcmp(ft_find_name_var(own_arg[(*i)]),
					"PWD") == 0 && (*env).pwd == false)
			|| (ft_strcmp(ft_find_name_var(own_arg[(*i)]),
					"SHLVL") == 0 && (*env).shlvl == false)
			|| (ft_strcmp(ft_find_name_var(own_arg[(*i)]),
					"HOME") == 0 && (*env).home == false)
			|| (ft_strcmp(ft_find_name_var(own_arg[(*i)]),
					"PATH") == 0 && (*env).path == false))
		{
			(*i)++;
			continue ;
		}
		else
		{
			ft_env_in_in(i, own_arg, env);
		}
	}
}

bool	ft_env(char **envp, t_env *env, t_mini *shell)
{
	int		i;
	char	**own_arg;

	i = 0;
	own_arg = ft_copy_envp_no_sort(envp);
	own_arg = ft_own_args(&own_arg, env, 0);
	if (shell->tab_pars[shell->tab_index + 1] != NULL
		&& shell->tab_pars[shell->tab_index + 1][0] != '|'
		&& shell->tab_pars[shell->tab_index + 1][0] != '>'
		&& shell->tab_pars[shell->tab_index + 1][0] != '<')
	{
		shell->status = 1;
		return (syntax_error(MANY_ARGS));
	}
	ft_env_in(env, own_arg, &i);
	return (true);
}
