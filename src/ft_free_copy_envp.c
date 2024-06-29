/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_copy_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:32:54 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:56 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_copy_envp(t_env *env)
{
	int	i;

	i = 0;
	while ((*env).copy_envp[i])
	{
		free((*env).copy_envp[i]);
		i++;
	}
	free((*env).copy_envp);
	free(env);
}
