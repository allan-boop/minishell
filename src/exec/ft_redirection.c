#include "../../include/minishell.h"

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
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (r);
}

static void	ft_parent_process(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
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
		close(fd[0]);
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
			shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		i++;
	}
}
