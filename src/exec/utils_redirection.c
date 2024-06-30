/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahans <ahans@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:33:23 by ahans             #+#    #+#             */
/*   Updated: 2024/06/30 14:00:25 by ahans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_open_fd(t_mini *shell, int i)
{
	if (shell->tab_pars[i][0] == '>'
		&& shell->tab_pars[i][1] == '>' && shell->tab_pars[i + 1])
	{
		shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
				| O_CREAT | O_APPEND, 0777);
	}
	else if (shell->tab_pars[i][0] == '>' && shell->tab_pars[i + 1])
	{
		shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0777);
	}
}