#include "../../include/minishell.h"

void	ft_find_dpoint(char **str, int *i, int *start, char **new)
{
	int	j;

	if ((*str)[*i] == '.' && (*str)[*i + 1] == '.' && ((*str)[*i + 2] == '/'
			|| (*str)[*i + 2] == '\0') && *start == 0)
	{
		j = (*i) - 2;
		while ((*str)[j] != '/')
			j--;
		while (*start < j)
		{
			(*new)[0] = (*str)[*start];
			(*start)++;
			(*new)++;
		}
		*i += 3;
		*start = *i;
		if ((*str)[*i])
		{
			(*new)[0] = '/';
			(*new)++;
		}
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
	new = (char *)ft_calloc(ft_strlen(*str) + 1, sizeof(char));
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

void	ft_change_path_ext(t_mini *shell, char **oldcwd)
{
	if (shell->tab_pars[1] && shell->tab_pars[1][0] != '\0'
			&& (*oldcwd)[ft_strlen(*oldcwd) - 1] != '/')
		*oldcwd = ft_strjoin_shell(*oldcwd, "/");
	if (shell->tab_pars[1])
		*oldcwd = ft_strjoin_shell(*oldcwd, shell->tab_pars[1]);
	while (*oldcwd && ft_strnstr(*oldcwd, "..", ft_strlen(*oldcwd)) != 0)
		*oldcwd = ft_clean_dpoint(oldcwd, 0);
	if (*oldcwd)
		chdir(*oldcwd);
}

void	ft_change_path( t_mini *shell, char **envp, char **oldcwd)
{
	if (shell->tab_pars[1] == NULL || shell->tab_pars[1][0] == '~')
	{
		*oldcwd = ft_getenv("HOME", envp);
		if (shell->tab_pars[1] && shell->tab_pars[1][0] == '~')
			shell->tab_pars[1]++;
		if (shell->tab_pars[1] && shell->tab_pars[1][0] == '/')
			shell->tab_pars[1]++;
	}
	else if (shell->tab_pars[1][0] == '.' && shell->tab_pars[1][1] == '/')
		shell->tab_pars[1] += 2;
	if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "-") == 0)
		*oldcwd = ft_getenv("OLDPWD", envp);
	else if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "/") == 0)
		*oldcwd = ft_strdup_shell("/");
	else if (shell->tab_pars[1] && ft_strcmp(shell->tab_pars[1], "//") == 0)
		*oldcwd = ft_strdup_shell(shell->tab_pars[1]);
	else
		ft_change_path_ext(shell, oldcwd);
}
