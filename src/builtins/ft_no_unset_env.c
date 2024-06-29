/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_unset_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:10 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:11 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	no_unset_env(t_mini *shell, t_env *env)
{
	if (ft_strcmp(shell->tab_pars[shell->tab_index], "PWD") == 0
		|| ft_strcmp(shell->tab_pars[shell->tab_index], "OLDPWD") == 0
		|| ft_strcmp(shell->tab_pars[shell->tab_index], "HOME") == 0
		|| ft_strcmp(shell->tab_pars[shell->tab_index], "SHLVL") == 0
		|| ft_strcmp(shell->tab_pars[shell->tab_index], "PATH") == 0)
	{
		if (ft_strcmp(shell->tab_pars[shell->tab_index], "PWD") == 0)
			(*env).pwd = false;
		if (ft_strcmp(shell->tab_pars[shell->tab_index], "OLDPWD") == 0)
			(*env).oldpwd = false;
		if (ft_strcmp(shell->tab_pars[shell->tab_index], "HOME") == 0)
			(*env).home = false;
		if (ft_strcmp(shell->tab_pars[shell->tab_index], "SHLVL") == 0)
			(*env).shlvl = false;
		if (ft_strcmp(shell->tab_pars[shell->tab_index], "PATH") == 0)
			(*env).path = false;
		return (true);
	}
	return (false);
}
