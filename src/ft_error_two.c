/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:32:49 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:32:50 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_malloc(char **tab_shell)
{
	int	i;

	i = 0;
	syntax_error(MALLOC_FAIL);
	while (tab_shell[i])
		free(tab_shell[i++]);
	free(tab_shell);
	return ;
}
