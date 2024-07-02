/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipefd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahans <ahans@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:25 by gdoumer           #+#    #+#             */
/*   Updated: 2024/07/02 13:36:50 by ahans            ###   ########.fr       */
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

void	ft_close_pipe_ter(t_mini *shell)
{
	printf("5\n");
	close_fd(shell->filein);
	close_fd(shell->fileout);
	dup2(shell->og_stdin, STDIN_FILENO);
	printf("6\n");
	dup2(shell->og_stdout, STDOUT_FILENO);
	shell->filein = -1;
	shell->fileout = -1;
}
