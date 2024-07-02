/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:39 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:41 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	inc_shlvl(t_mini *shell, t_env *env)
{
	int		j;
	char	*shlvl;

	if (ft_strcmp_shell(shell->tab_cmd[shell->i], "./minishell") == 0)
	{
		shlvl = ft_getenv("SHLVL", (*env).copy_envp);
		j = ft_atoi(shlvl);
		j++;
		shlvl = ft_itoa(j);
		ft_setenv("SHLVL", shlvl, &((*env).copy_envp));
	}
}
