#include "../../include/minishell.h"

void	ft_find_dpoint(char **str, int *i, int *start, char **new)
{
	if ((*str)[*i] == '.' && (*str)[*i + 1] && (*str)[*i + 1] == '.'
			&& (((*str)[*i + 2] && (*str)[*i + 2] == '/')
			|| (*str)[*i + 2] == '\0') && *start == 0)
	{
		ft_find_dpointb(i, start, str, new);
	}
	else
		(*i)++;
}

char	*ft_clean_dpoint(char **str, int i)
{
	char	*new;
	int		start;
	char	*tmp;

	start = 0;
	new = (char *)ft_calloc_shell(ft_strlen(*str) + 1, sizeof(char));
	tmp = new;
	while ((*str)[i])
		ft_find_dpoint(str, &i, &start, &new);
	while ((*str)[start])
	{
		new[0] = (*str)[start++];
		new++;
	}
	return (tmp);
}

char	*ft_clean_point(char **str, int i, int j)
{
	char	*new;

	new = (char *)ft_calloc_shell(ft_strlen(*str) + 1, sizeof(char));
	if (*str)
	{
		while ((*str)[i])
		{
			if ((*str)[i] == '.' && (*str)[i + 1] && (*str)[i + 1] == '.')
			{
				new[j++] = (*str)[i++];
				new[j++] = (*str)[i++];
			}
			if ((*str)[i] == '.')
			{
				i++;
				if ((*str)[i] == '/')
					i++;
			}
			else if (i > 0 && (*str)[i] == '/' && (*str)[i - 1] == '/')
				i++;
			else if ((*str)[i])
				new[j++] = (*str)[i++];
		}
	}
	return (new);
}

void	ft_change_path_ext(t_mini *shell, char **oldcwd)
{
	if (shell->tab_pars[1] && shell->tab_pars[1][0] != '\0'
			&& ft_strlen(*oldcwd) > 0
			&& (*oldcwd)[ft_strlen(*oldcwd) - 1] != '/')
		*oldcwd = ft_strjoin_shell(*oldcwd, "/");
	if (shell->tab_pars[1])
	{
		if (shell->tab_pars[1][0] == '/')
		{
			while (shell->tab_pars[1][1] && shell->tab_pars[1][1] == '/')
				shell->tab_pars[1]++;
			*oldcwd = ft_strdup_shell(shell->tab_pars[1]);
		}
		else
			*oldcwd = ft_strjoin_shell(*oldcwd, shell->tab_pars[1]);
	}
	*oldcwd = ft_clean_point(oldcwd, 0, 0);
	while (*oldcwd && ft_strnstr(*oldcwd, "..", ft_strlen(*oldcwd)) != 0)
		*oldcwd = ft_clean_dpoint(oldcwd, 0);
	if (*oldcwd)
		chdir(*oldcwd);
}

void	ft_change_path( t_mini *shell, t_env *env, char **oldcwd)
{
	if (shell->tab_pars[1] == NULL || shell->tab_pars[1][0] == '~')
	{
		*oldcwd = ft_getenv("HOME", (*env).copy_envp);
		if (shell->tab_pars[1] && shell->tab_pars[1][0] == '~')
			shell->tab_pars[1]++;
		while (shell->tab_pars[1] && shell->tab_pars[1][0] == '/')
			shell->tab_pars[1]++;
	}
	else if (shell->tab_pars[1][0] == '.' && shell->tab_pars[1][1] == '/')
		shell->tab_pars[1] += 2;
	if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "-") == 0)
		*oldcwd = ft_strdup_shell(ft_getenv("OLDPWD", (*env).copy_envp));
	else if (shell->tab_pars[1] && (ft_strcmp(shell->tab_pars[1], "/") == 0
			|| ft_strcmp(shell->tab_pars[1], "/.") == 0))
		*oldcwd = ft_strdup("/");
	else if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "//") == 0)
		*oldcwd = ft_strdup_shell(shell->tab_pars[1]);
	else
		ft_change_path_ext(shell, oldcwd);
}
