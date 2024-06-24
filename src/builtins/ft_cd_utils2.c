#include "../../include/minishell.h"

void	ft_find_dpointb(int *i, int *start, char **str, char **new)
{
	int	j;

	j = (*i) - 2;
	while (j > 0 && (*str)[j] != '/')
		j--;
	while (*start < j)
	{
		(*new)[0] = (*str)[*start];
		(*start)++;
		(*new)++;
	}
	if ((*str)[*i + 2])
		*i += 3;
	else
		*i += 2;
	*start = *i;
	if ((*str)[*i])
	{
		(*new)[0] = '/';
		(*new)++;
	}
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	ft_cd_logic_error(t_mini *shell, char *path)
{
	if (chdir(path) == -1 || (shell->tab_pars[shell->tab_index] != NULL
			&& shell->tab_pars[shell->tab_index][0] != '|'))
	{
		shell->status = 1;
		free(path);
		return (ft_error("cd", strerror(errno), 1));
	}
	free(path);
	shell->status = 0;
	return (0);
}

bool	check_cd_err(t_mini *shell, char *path)
{
	if (shell->tab_pars[shell->tab_index] != NULL)
		shell->tab_index++;
	if (ft_cd_logic_error(shell, path) == 1)
		return (true);
	return (false);
}
