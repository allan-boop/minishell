/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:34 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/30 15:14:06 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	gnl(char **line, int i, int r, char c)
{
	char	*buffer;

	buffer = (char *)ft_alloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	if (g_sig == SIGINT)
		return (-1);
	while (r && c && c != '\n' && c != '\0')
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

void	ft_here_doc_in(t_env *env, int *fd, t_mini *shell)
{
	close_fd(fd[0]);
	close_fd(fd[1]);
	close_fd(shell->filein);
	close_fd(shell->fileout);
	close_fd(shell->og_stdin);
	close_fd(shell->og_stdout);
	ft_del_all();
	ft_free_copy_envp(env);
	exit(EXIT_SUCCESS);
}

void	ft_here_doc_while(t_mini *shell, int *i, t_env *env, int *fd)
{
	char	*line;

	(void)env;
	while (gnl(&line, 0, 0, 0))
	{
		if (g_sig == SIGINT)
			break ;
		if (ft_strncmp(line, shell->tab_pars[*i + 1],
				ft_strlen(shell->tab_pars[*i + 1])) == 0
			&& ft_strlen(line) - 1 == ft_strlen(shell->tab_pars[*i + 1]))
			ft_here_doc_in(env, fd, shell);
		write(fd[1], line, ft_strlen(line));
		write(1, "> ", 2);
	}
}
