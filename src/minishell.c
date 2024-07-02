/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:33:11 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:33:14 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	set_env(envp, env, argc, argv);
	ft_loop(envp, env);
	return (0);
}
