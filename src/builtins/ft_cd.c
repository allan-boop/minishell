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
			free((*envp)[*i]);
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
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	free(new);
	new = ft_strjoin(name, "=");
	new = ft_strjoin(new, value);
	new_envp[i] = new;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}

static bool	ft_cd_logic( t_mini *shell, t_env *env)
{
	char	*path;
	char	*tmp;

	if (shell->tab_pars[shell->tab_index] == NULL
		|| shell->tab_pars[shell->tab_index][0] == '~')
	{
		path = ft_strdup(ft_getenv("HOME", (*env).copy_envp));
		if (shell->tab_pars[shell->tab_index]
			&& shell->tab_pars[shell->tab_index][1] != '\0')
		{
			tmp = path;
			path = ft_strjoin(path, shell->tab_pars[shell->tab_index]
					+ 1);
			free(tmp);
		}
		if (path == NULL)
			return (ft_error("cd", "HOME not set", 1));
	}
	else if (ft_strcmp(shell->tab_pars[shell->tab_index], "-") == 0)
	{
		path = ft_strdup(ft_getenv("OLDPWD", (*env).copy_envp));
		if (path == NULL)
		{
			free(path);
			return (ft_error("cd", "OLDPWD not set", 1));
		}
	}
	else
		path = ft_strdup(shell->tab_pars[shell->tab_index]);
	return (check_cd_err(shell, path));
}

static void	ft_change_env(t_env *env, char *oldpwd, char *oldcwd)
{
	int	i;

	i = 0;
	i = ft_strlen(oldcwd) - 1;
	while (i > 2 && oldcwd[i] == '/')
		oldcwd[i--] = '\0';
	ft_setenv("OLDPWD", oldpwd, &((*env).copy_envp));
	if (oldcwd[0] == '\0' && (oldcwd[0] != '/' && oldcwd[1] != '\0'))
		oldcwd = ft_strdup("/");
	ft_setenv("PWD", oldcwd, &((*env).copy_envp));
	if (oldcwd[0] == '/' && oldcwd[1] == '\0')
		free(oldcwd);
}

bool	ft_cd(t_mini *shell, t_env *env)
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
	oldpwd = ft_getenv("PWD", (*env).copy_envp);
	oldcwd = ft_getenv("PWD", (*env).copy_envp);
	if (ft_cd_logic(shell, env) == 1)
		return (true);
	ft_change_path(shell, env, &oldcwd);
	if (!oldcwd)
	{
		ft_setenv("OLDPWD", oldpwd, &((*env).copy_envp));
		ft_setenv("PWD", oldpwd, &((*env).copy_envp));
		return (true);
	}
	ft_change_env(env, oldpwd, oldcwd);
	return (true);
}
