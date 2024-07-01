/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:31:37 by gdoumer           #+#    #+#             */
/*   Updated: 2024/07/01 17:12:54 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_access_exec(char *path, char **tab_shell, t_env *env)
{
	if (tab_shell[0][0] == '>' || tab_shell[0][0] == '<')
		return (-1);
	if (!path)
		path = find_path_execve_vol_two(tab_shell[0]);
	if (!path)
	{
		printf("%s : command not found\n", tab_shell[0]);
		return (-1);
	}
	if (access(path, F_OK) == -1 && access(path, X_OK) == -1)
	{
		ft_error_malloc(tab_shell);
		return (-1);
	}
	if ((*env).path == false)
	{
		printf("%s : command not found\n", tab_shell[0]);
		return (-1);
	}
	if (execve(path, tab_shell, (*env).copy_envp) == -1)
	{
		syntax_error(ERROR_EXECVE);
		return (-1);
	}
	return (0);
}

int	ft_execve(char *str, t_env *env)
{
	char	*path;
	char	**tab_shell;
	int		j;

	ft_replace_space(&str);
	tab_shell = ft_split_shell(str, ' ');
	j = 0;
	while (tab_shell[j])
	{
		tab_shell[j] = ft_clean_quotes(tab_shell[j]);
		j++;
	}
	ft_put_space_between(tab_shell);
	if (!tab_shell)
		return (-1);
	path = find_path_execve(tab_shell[0], (*env).copy_envp);
	if (!path && access(tab_shell[0], F_OK) == 0
		&& access(tab_shell[0], X_OK) == 0
		&& tab_shell[0][0] == '.' && tab_shell[0][1] == '/')
		path = ft_strdup_shell(tab_shell[0]);
	if (ft_access_exec(path, tab_shell, env) == -1)
		return (-1);
	return (0);
}

bool	other_builtin(char *cmd, t_env *env)
{
	if (cmd[0] && ft_execve(cmd, env) == 0)
		return (true);
	return (false);
}

void	ft_parent(pid_t pid, int *pipefd, char *cmd_next, t_mini *shell)
{
	if (cmd_next != NULL)
	{
		if (shell->filein == -1)
		{
			dup2(pipefd[0], STDIN_FILENO);
		}
	}
	else
	{
		if (shell->filein == -1)
		{
			dup2(shell->og_stdin, STDIN_FILENO);
		}
		signal(SIGQUIT, proc_signal_handler);
		waitpid(pid, &(shell->status), 0);
		if (WIFSIGNALED(shell->status))
			shell->status = WTERMSIG(shell->status) + 128;
		else
			if (WIFEXITED(shell->status))
				shell->status = WEXITSTATUS(shell->status);
	}
	close_fd(pipefd[1]);
	close_fd(pipefd[0]);
}

bool	other_builtin_p(char *cmd, t_env *env, char *cmd_next, t_mini *shell)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		syntax_error(ERROR_FORK);
		return (false);
	}
	if (pid == 0)
	{
		inc_shlvl(shell, env);
		if (cmd_next != NULL)
		{
			if (shell->fileout == -1)
				dup2(pipefd[1], STDOUT_FILENO);
		}
		ft_close_pipefd_bis(shell, pipefd);
		if (cmd[0] && ft_execve(cmd, env) == 0)
			ft_execve(cmd, env);
		ft_free_copy_envp(env);
		ft_del_all();
		exit(1);
	}
	ft_parent(pid, pipefd, cmd_next, shell);
	return (true);
}
