#include "../../include/minishell.h"

static char	*ft_setenv_index(char *name, char ***envp, char *value, int *i)
{
	int		len;
	char	*new;
	char	*tmp;

	len = ft_strlen(name);
	new = NULL;
	tmp = NULL;
	while ((*envp)[*i] != NULL)
	{
		if (ft_strncmp(name, (*envp)[*i], len) == 0)
		{
			new = ft_strjoin(name, "=");
			tmp = ft_strjoin(new, value);
			(*envp)[*i] = tmp;
			free(new);
			return (NULL);
		}
		(*i)++;
	}
	return (new);
}

void	ft_setenv(char *name, char *value, char ***envp)
{
	int		i;
	char	*new;
	char	**new_envp;

	i = 0;
	new = ft_setenv_index(name, envp, value, &i);
	if (new == NULL)
		return ;
	new_envp = ft_alloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new = ft_strjoin(name, "=");
	new = ft_strjoin(new, value);
	new_envp[i] = new;
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}

static bool	ft_cd_logic( t_mini *shell, char **envp)
{
	char	*path;

	if (shell->tab_pars[shell->tab_index] == NULL
		|| shell->tab_pars[shell->tab_index][0] == '~')
	{
		path = ft_getenv("HOME", envp);
		if (shell->tab_pars[shell->tab_index]
			&& shell->tab_pars[shell->tab_index][1] != '\0')
			path = ft_strjoin_shell(path, shell->tab_pars[shell->tab_index]
					+ 1);
		if (path == NULL)
			return (ft_error("cd", "HOME not set", 1));
	}
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "-") == 0)
	{
		path = ft_getenv("OLDPWD", envp);
		if (path == NULL)
			return (ft_error("cd", "OLDPWD not set", 1));
	}
	else
		path = shell->tab_pars[shell->tab_index];
	return (check_cd_err(shell, path));
}

static void	ft_change_env(char **envp, char *oldpwd, char *oldcwd)
{
	int	i;

	i = 0;
	i = ft_strlen(oldcwd) - 1;
	while (i > 2 && oldcwd[i] == '/')
		oldcwd[i--] = '\0';
	ft_setenv("OLDPWD", oldpwd, &envp);
	if (oldcwd[0] == '\0')
		oldcwd = ft_strdup("/");
	ft_setenv("PWD", oldcwd, &envp);
}

bool	ft_cd(t_mini *shell, char **envp)
{
	char		*oldpwd;
	char		*oldcwd;

	shell->tab_index++;
	dup2(shell->og_stdout, STDOUT_FILENO);
	if (shell->tab_pars[shell->tab_index])
		ft_dell_all_quote_export(shell->tab_pars[shell->tab_index]);
	if (shell->tab_pars[shell->tab_index]
		&& shell->tab_pars[shell->tab_index + 1]
		&& shell->tab_pars[shell->tab_index + 1][0] != '|')
		return (ft_error("cd", "too many arguments", 1));
	oldpwd = ft_getenv("PWD", envp);
	oldcwd = ft_getenv("PWD", envp);
	if (ft_cd_logic(shell, envp) == 1)
		return (true);
	ft_change_path(shell, envp, &oldcwd);
	if (!oldcwd)
	{
		ft_setenv("OLDPWD", oldpwd, &envp);
		ft_setenv("PWD", oldpwd, &envp);
		return (true);
	}
	ft_change_env(envp, oldpwd, oldcwd);
	return (true);
}
