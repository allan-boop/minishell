#include "../../include/minishell.h"

static size_t	ft_count_args(t_mini *shell)
{
	size_t		nb_args;
	t_mini		tmp;

	tmp = *shell;
	nb_args = 0;
	while (tmp.tab_pars[tmp.tab_index + 1]
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '|'
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '<'
		&& tmp.tab_pars[tmp.tab_index + 1][0] != '>')
	{
		tmp.tab_index++;
		nb_args++;
	}
	return (nb_args);
}

static bool	ft_check_unset(t_mini *shell)
{
	if (!shell)
		return (false);
	if (shell->tab_pars[shell->tab_index + 1] == NULL)
	{
		syntax_error(NOT_ENOUGH_ARG);
		return (false);
	}
	if (shell->tab_pars[shell->tab_index + 1][0] == '-'
		&& shell->tab_pars[shell->tab_index + 1][1] != '\0')
	{
		shell->status = 1;
		syntax_error(INVALID_OPTION);
		return (false);
	}
	return (true);
}

bool	ft_in_in_unset(t_env *env, size_t *i, size_t *nb_args)
{
	while ((*env).copy_envp[*i])
	{
		free((*env).copy_envp[*i]);
		(*env).copy_envp[*i] = ft_strdup((*env).copy_envp[*i + 1]);
		(*i)++;
	}
	if (*nb_args == 0)
		return (true);
	return (false);
}

static bool	ft_in_unset(t_env *env, t_mini *shell, size_t *i, size_t *nb_args)
{
	char		*name;
	size_t		len;

	name = ft_find_name_var(shell->tab_pars[shell->tab_index]);
	len = ft_strlen(name);
	while ((*env).copy_envp[*i] && shell->tab_pars[shell->tab_index]
		&& (shell->tab_pars[shell->tab_index][0] != '|'
		&& shell->tab_pars[shell->tab_index][0] != '<'
			&& shell->tab_pars[shell->tab_index][0] != '>'))
	{
		if (no_unset_env(shell, env) == true)
			(*i)++;
		else if (ft_strncmp((*env).copy_envp[*i], name, len) == 0
			&& shell->tab_pars[shell->tab_index][len] != '='
			&& ((*env).copy_envp[*i][len] == '='
				|| (*env).copy_envp[*i][len] == '\0'))
			ft_in_in_unset(env, i, nb_args);
		else
			(*i)++;
	}
	return (false);
}

bool	ft_unset(t_mini *shell, t_env *env)
{
	size_t		i;
	size_t		nb_args;

	shell->status = 0;
	if (ft_check_unset(shell) == false)
		return (true);
	nb_args = ft_count_args(shell);
	while (nb_args > 0 && shell->tab_pars[shell->tab_index + 1]
		&& shell->tab_pars[shell->tab_index + 1][0] != '|'
		&& shell->tab_pars[shell->tab_index + 1][0] != '<'
		&& shell->tab_pars[shell->tab_index + 1][0] != '>')
	{
		shell->tab_index++;
		nb_args--;
		i = 0;
		if (ft_in_unset(env, shell, &i, &nb_args) == true)
			return (true);
	}
	return (true);
}
