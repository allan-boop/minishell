#include "../../include/minishell.h"

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

	if (shell->tab_pars[1] == NULL)
	{
		path = ft_getenv("HOME", envp);
		if (path == NULL)
			return (ft_error("cd", "HOME not set", 1));
	}
	else if (ft_strcmp(shell->tab_pars[1], "-") == 0)
	{
		path = ft_getenv("OLDPWD", envp);
		if (path == NULL)
			return (ft_error("cd", "OLDPWD not set", 1));
		ft_printf("%s\n", path);
	}
	else
		path = shell->tab_pars[1];
	if (chdir(path) == -1)
		return (ft_error("cd", strerror(errno), 1));
	return (false);
}

bool	ft_cd(t_mini *shell, char **envp)
{
	char	*oldpwd;
	char	*oldcwd;

	oldpwd = getcwd(NULL, 0);
	if (ft_cd_logic(shell, envp) == 1)
		return (true);
	ft_setenv("OLDPWD", oldpwd, &envp);
	oldcwd = getcwd(NULL, 0);
	ft_setenv("PWD", oldcwd, &envp);
	free(oldcwd);
	free(oldpwd);
	return (true);
}
