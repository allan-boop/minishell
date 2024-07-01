/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_b_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:20 by gdoumer           #+#    #+#             */
/*   Updated: 2024/07/01 17:41:19 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	other_b_in(char *cmd, t_env *env)
{
	if (cmd[0] && ft_execve(cmd, env) == 0)
		ft_execve(cmd, env);
	ft_free_copy_envp(env);
	ft_del_all();
}
