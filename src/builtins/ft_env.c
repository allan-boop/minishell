/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:48 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:30:50 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_own_args_in(t_env *env, int *i, int *k, char ***new_envp)
{
	while ((*env).copy_envp[(*i)])
	{
		if (ft_getenv(ft_find_name_var((*env).copy_envp[(*i)]),
				(*new_envp)) == NULL)
		{
			(*new_envp)[(*k)++] = ft_strdup_shell((*env).copy_envp[(*i)++]);
			(*new_envp)[(*k)] = NULL;
		}
		else
			(*i)++;
	}
}

static char	**ft_own_args(char ***own_arg, t_env *env, int i)
{
	int		k;
	char	**new_envp;

	k = 0;
	new_envp = ft_alloc(sizeof(char *) * (ft_tab_len((*env).copy_envp) + 2));
	while ((*own_arg)[i])
	{
		if (ft_getenv(ft_find_name_var((*own_arg)[i]),
			(*env).copy_envp) != NULL)
			new_envp[k++] = ft_strdup_shell((*own_arg)[i]);
		i++;
	}
	new_envp[k] = NULL;
	i = 0;
	ft_own_args_in(env, &i, &k, &new_envp);
	i = -1;
	while ((*own_arg)[++i])
		free((*own_arg)[i]);
	free(*own_arg);
	return (new_envp);
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
			ft_printf("%s\n", own_arg[(*i)]);
			(*i)++;
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
