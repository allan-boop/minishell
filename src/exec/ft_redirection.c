/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:31 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:31:33 by gdoumer          ###   ########.fr       */
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

static void	ft_parent_process(int *fd)
{
	signal(SIGINT, proc_signal_handler_heredoc_parent);
	close_fd(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close_fd(fd[0]);
	wait(NULL);
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
		close_fd(fd[0]);
		ft_here_doc_while(shell, i, env, fd);
		ft_here_doc_in(env, fd, shell);
	}
	else
		ft_parent_process(fd);
	(*i)++;
}

void	ft_redirection(t_mini *shell, t_env *env)
{
	int		i;
	int		fd[2];

	(void)env;
	i = shell->tab_index;
	shell->filein = -1;
	shell->fileout = -1;
	while (shell->tab_pars[i] && shell->tab_pars[i][0] != '|')
	{
		if (shell->tab_pars[i][0] == '<'
				&& shell->tab_pars[i][1] == '<' && shell->tab_pars[i + 1])
			ft_here_doc(shell, &i, fd, env);
		else if (shell->tab_pars[i][0] == '<' && shell->tab_pars[i + 1])
			shell->filein = open(shell->tab_pars[i + 1], O_RDONLY);
		if (shell->tab_pars[i][0] == '>'
			&& shell->tab_pars[i][1] == '>' && shell->tab_pars[i + 1])
			shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
					| O_CREAT | O_APPEND, 0777);
		else if (shell->tab_pars[i][0] == '>' && shell->tab_pars[i + 1])
		{
			shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		}
		i++;
	}
}
