/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:12 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:13 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_pwd(t_mini *shell, t_env *env)
{
	char	*path;

	path = ft_getenv("PWD", (*env).copy_envp);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	shell->status = 0;
	return (true);
}
