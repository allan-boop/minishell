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

int	gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)ft_alloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	if (g_sig == SIGINT)
		return (-1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
		if (g_sig == SIGINT)
			return (-1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	if (r == 0)
		write(1, "\n", 1);
	return (r);
}

static void	ft_parent_process(int *fd)
{
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
		signal(SIGQUIT, signal_handler);
		write(1, "> ", 2);
		while (gnl(&line))
		{
			if (g_sig == SIGINT)
				break ;
			if (!ft_strncmp(line, shell->tab_pars[1],
					ft_strlen(shell->tab_pars[1])))
				break ;
			write(1, "> ", 2);
		}
	}
}

void	ft_here_doc(t_mini *shell, int *i, int *fd)
{
	char	*line;
	pid_t	reader;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	reader = fork();
	if (reader == 0)
	{
		write(1, "> ", 2);
		close_fd(fd[0]);
		while (gnl(&line))
		{
			write(1, "> ", 2);
			if (ft_strncmp(line, shell->tab_pars[*i + 1],
					ft_strlen(shell->tab_pars[*i + 1])) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
		ft_parent_process(fd);
	(*i)++;
}

void	ft_redirection(t_mini *shell)
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
			ft_here_doc(shell, &i, fd);
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
