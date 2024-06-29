/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:51 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:53:30 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exit_in_bis(t_env *env, t_mini **shell)
{
	int		i;

	i = 0;
	while ((*env).copy_envp[i])
	{
		free((*env).copy_envp[i]);
		i++;
	}
	close_fd((*shell)->og_stdin);
	close_fd((*shell)->og_stdout);
	free((*env).copy_envp);
	free(env);
	ft_del_all();
}

static bool	error_exit(t_mini **shell, int i, t_env *env)
{
	if ((*shell)->tab_pars[(*shell)->tab_index + 1] != NULL
		&& (*shell)->tab_pars[(*shell)->tab_index + 2] != NULL)
		return (true);
	if ((*shell)->tab_pars[(*shell)->tab_index + 1] != NULL)
	{
		while ((*shell)->tab_pars[(*shell)->tab_index + 1][i])
		{
			if (ft_isalpha((*shell)->tab_pars[(*shell)->tab_index + 1][i]))
			{
				ft_printf("exit: %s: numeric argument required\n",
					(*shell)->tab_pars[(*shell)->tab_index + 1]);
				ft_exit_in_bis(env, shell);
				exit (2);
			}
			i++;
		}
	}
	return (false);
}

static void	ft_exit_in(t_env *env, t_mini **shell, char *shlvl, char **tmp)
{
	int		i;

	i = 0;
	while ((*env).copy_envp[i])
	{
		free((*env).copy_envp[i]);
		i++;
	}
	free(shlvl);
	free(tmp);
	close_fd((*shell)->og_stdin);
	close_fd((*shell)->og_stdout);
	free(env);
	ft_del_all();
}

bool	ft_exit(char **envp, t_env *env, t_mini **shell)
{
	int		j;
	char	*shlvl;
	char	**tmp;
	int		ret_val;

	if (error_exit(shell, 0, env) == true)
		return (syntax_error(MANY_ARGS));
	shlvl = ft_getenv("SHLVL", envp);
	tmp = (*env).copy_envp;
	j = ft_atoi(shlvl);
	j--;
	ret_val = ft_atoi((*shell)->tab_pars[(*shell)->tab_index + 1]);
	shlvl = ft_itoa(j);
	ft_setenv_shell("SHLVL", shlvl, &envp);
	ft_printf("exit\n");
	ft_exit_in(env, shell, shlvl, tmp);
	ret_val = ret_val % 256;
	exit(ret_val);
	return (true);
}
