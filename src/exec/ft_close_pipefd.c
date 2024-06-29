/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipefd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:25 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:26 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_close_pipefd(t_mini *shell)
{
	close_fd(shell->pipe_fd[shell->i_p][1]);
	close_fd(shell->pipe_fd[shell->i_p][0]);
	close_fd(shell->fileout);
}

void	ft_close_pipefd_bis(t_mini *shell, int pipefd[2])
{
	close_fd(pipefd[0]);
	close_fd(pipefd[1]);
	close_fd(shell->og_stdin);
	close_fd(shell->og_stdout);
}
