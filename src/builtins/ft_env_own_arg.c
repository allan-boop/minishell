/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_own_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:18:11 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 16:18:33 by gdoumer          ###   ########.fr       */
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

char	**ft_own_args(char ***own_arg, t_env *env, int i)
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
