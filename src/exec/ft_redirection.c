/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:31 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/30 15:31:36 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir(t_mini *shell, char *cmd_next)
{
	if (!cmd_next && shell->og_stdout == -1)
		dup2(shell->og_stdout, STDOUT_FILENO);
	if (shell->fileout != -1)
	{
		dup2(shell->fileout, STDOUT_FILENO);
		close_fd(shell->fileout);
	}
	if (shell->filein != -1)
	{
		dup2(shell->filein, STDIN_FILENO);
		close_fd(shell->filein);
	}
}

static void	ft_parent_process(t_mini *shell, int *fd, pid_t pid)
{
	signal(SIGINT, proc_signal_handler_heredoc_parent);
	signal(SIGQUIT, proc_signal_handler_heredoc_parent);
	waitpid(pid, NULL, 0);
	close_fd(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close_fd(fd[0]);
	close_fd(shell->fileout);
}

void	ft_mini_doc(t_mini *shell)
{
	char				*line;
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = proc_signal_handler_heredoc;
	if (shell->tab_pars[0][0] == '<'
			&& shell->tab_pars[0][1] == '<' && shell->tab_pars[1])
	{
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		write(1, "> ", 2);
		while (gnl(&line, 0, 0, 0))
		{
			if (g_sig == SIGINT)
				break ;
			if (!ft_strncmp(line, shell->tab_pars[1],
					ft_strlen(shell->tab_pars[1]))
				&& ft_strlen(line) - 1 == ft_strlen(shell->tab_pars[1]))
				break ;
			write(1, "> ", 2);
		}
	}
	ft_open_fd(shell, 0);
	g_sig = 0;
}

void	ft_here_doc(t_mini *shell, int *i, int *fd, t_env *env)
{
	pid_t				reader;
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = proc_signal_handler_heredoc;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	reader = fork();
	if (reader == 0)
	{
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		write(1, "> ", 2);
		dup2(shell->og_stdin, STDIN_FILENO);
		dup2(shell->og_stdout, STDOUT_FILENO);
		ft_here_doc_while(shell, i, env, fd);
		ft_here_doc_in(env, fd, shell);
	}
	else
		ft_parent_process(shell, fd, reader);
	(*i)++;
}

int	ft_redirection(t_mini *shell, t_env *env)
{
	int		i;
	int		fd[2];

	i = shell->tab_index;
	shell->filein = -1;
	shell->fileout = -1;
	while (shell->tab_pars[i] && shell->tab_pars[i][0] != '|')
	{
		if (shell->tab_pars[i][0] == '<'
				&& shell->tab_pars[i][1] == '<' && shell->tab_pars[i + 1])
			ft_here_doc(shell, &i, fd, env);
		else if (shell->tab_pars[i][0] == '<' && shell->tab_pars[i + 1])
		{
			shell->filein = open(shell->tab_pars[i + 1], O_RDONLY);
			if (shell->filein == -1)
			{
				syntax_error(FILE_DIRECTORY);
				return (1);
			}
			dup2(shell->filein, STDIN_FILENO);
		}
		ft_open_fd(shell, i);
		i++;
	}
	return (0);
}
