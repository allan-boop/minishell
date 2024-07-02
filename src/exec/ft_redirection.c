/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahans <ahans@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:31 by gdoumer           #+#    #+#             */
/*   Updated: 2024/07/02 13:57:52 by ahans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir(t_mini *shell, char *cmd_next)
{
	if ((cmd_next && shell->v[shell->fd_i] == shell->cmd_count + 1)
		|| shell->cmd_count == shell->v[shell->fd_i])
	{
		if (shell->cmd_count == shell->v[shell->fd_i])
		{
			printf("fd %d\n", shell->hd_fd[shell->fd_i][1]);
			printf("9\n");
			dup2(shell->hd_fd[shell->fd_i][1], STDIN_FILENO);
			close_fd(shell->hd_fd[shell->fd_i][1]);
			shell->fd_i++;
		}
	}
	else
	{
		if (!cmd_next && shell->og_stdout == -1)
		{
			printf("1\n");
			dup2(shell->og_stdout, STDOUT_FILENO);
		}
		if (shell->fileout != -1)
		{
			printf("2\n");
			dup2(shell->fileout, STDOUT_FILENO);
			close_fd(shell->fileout);
		}
		if (shell->filein != -1)
		{
			printf("3\n");
			dup2(shell->filein, STDIN_FILENO);
			close_fd(shell->filein);
		}
	}
}

static void	ft_parent_process(t_mini *shell, int *fd, pid_t pid)
{
	(void)pid;
	signal(SIGINT, proc_signal_handler_heredoc_parent);
	signal(SIGQUIT, proc_signal_handler_heredoc_parent);
	waitpid(pid, &(shell->status), 0);
	//printf("10\n");
	//dup2(fd[0], STDIN_FILENO);
	close_fd(fd[0]);
	close_fd(fd[1]);
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

void	ft_here_doc(t_mini *shell, int *i, t_env *env)
{
	pid_t				reader;
	struct sigaction	act;
	int					*fd;

	fd = ft_alloc(sizeof(int) * 2);
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = proc_signal_handler_heredoc;
	if (pipe(fd) == -1)
	{
		exit(EXIT_FAILURE);
	}
	shell->hd_fd[shell->fd_i++] = fd;
	// shell->filein = fd[0];
	reader = fork();
	if (reader == 0)
	{
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		printf("11\n");
		dup2(shell->og_stdin, STDIN_FILENO);
		write(1, "> ", 2);
		ft_here_doc_whil(shell, i, env, fd);
		ft_here_doc_in(env, fd, shell);
	}
	else
		ft_parent_process(shell, fd, reader);
	(*i)++;
}

void	ft_heredoc(t_mini *shell, t_env *env)
{
	int		i;
	int		v;
	int		h;

	h = 0;
	v = 0;
	i = 0;
	shell->fd_i = 0;
	shell->hd_fd = ft_alloc(sizeof(int *) * 10 + 1);
	while (shell->tab_pars[i])
	{
		if (shell->tab_pars[i][0] == '|')
			v++;
		else if (shell->tab_pars[i][0] == '<'
				&& shell->tab_pars[i][1] == '<' && shell->tab_pars[i + 1])
		{
			ft_here_doc(shell, &i, env);
			shell->v[h++] = v;
		}
		i++;
	}
	shell->v[h] = -1;
	shell->fd_i = 0;
}

int	ft_redirection(t_mini *shell)
{
	int		i;

	i = shell->tab_index;
	shell->filein = -1;
	shell->fileout = -1;
	while (shell->tab_pars[i] && shell->tab_pars[i][0] != '|')
	{
		if (shell->tab_pars[i][0] == '<' && shell->tab_pars[i][1] == '\0'
			&& shell->tab_pars[i + 1])
		{
			shell->filein = open(shell->tab_pars[i + 1], O_RDONLY);
			if (shell->filein == -1)
			{
				syntax_error(FILE_DIRECTORY);
				return (1);
			}
			printf("12\n");
			dup2(shell->filein, STDIN_FILENO);
		}
		ft_open_fd(shell, i);
		i++;
	}
	return (0);
}
