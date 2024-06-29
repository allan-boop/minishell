/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:45 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:47 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_arg_fork(t_mini *shell)
{
	int	nb_pipe;

	nb_pipe = 1;
	while (shell->list != NULL)
	{
		if (shell->list->is_operator == true || shell->list->is_redir == true)
			nb_pipe++;
		shell->list = shell->list->next;
	}
	return (nb_pipe);
}
