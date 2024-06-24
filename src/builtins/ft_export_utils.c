#include "../../include/minishell.h"

bool	yes_unset_env(char *name, t_env *env)
{
	if (ft_strcmp(name, "PWD") == 0
		|| ft_strcmp(name, "OLDPWD") == 0
		|| ft_strcmp(name, "HOME") == 0
		|| ft_strcmp(name, "SHLVL") == 0
		|| ft_strcmp(name, "PATH") == 0)
	{
		if (ft_strcmp(name, "PWD") == 0)
			(*env).pwd = true;
		if (ft_strcmp(name, "OLDPWD") == 0)
			(*env).oldpwd = true;
		if (ft_strcmp(name, "HOME") == 0)
			(*env).home = true;
		if (ft_strcmp(name, "SHLVL") == 0)
			(*env).shlvl = true;
		if (ft_strcmp(name, "PATH") == 0)
			(*env).path = true;
		return (true);
	}
	return (false);
}

static char	*ft_print_export_else_two(char *new_value, char *value, size_t j)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\"')
			new_value[j++] = '\\';
		new_value[j] = value[i];
		i++;
		j++;
	}
	new_value[j] = 0;
	return (new_value);
}

static void	ft_print_export_else(char *value, t_envp *tmp)
{
	char	*new_value;
	size_t	i;
	size_t	j;
	size_t	nb_double_quote;

	i = 0;
	j = 0;
	nb_double_quote = 0;
	if (ft_strchr(value, '\"') != NULL)
	{
		while (value[i])
		{
			if (value[i] == '\"')
				nb_double_quote++;
			i++;
		}
		new_value = ft_alloc(sizeof(char) * (i + nb_double_quote + 1));
		new_value = ft_print_export_else_two(new_value, value, j);
		ft_printf("declare -x %s=\"%s\"\n", tmp->var, new_value);
	}
	else
		ft_printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
}

static void	ft_print_export(t_mini *shell, t_env *env)
{
	t_envp	*tmp;

	tmp = shell->team_envp;
	while (tmp)
	{
		if ((ft_strcmp(tmp->var, "OLDPWD") == 0 && (*env).oldpwd == false)
			|| (ft_strcmp(tmp->var, "PWD") == 0 && (*env).pwd == false)
			|| (ft_strcmp(tmp->var, "SHLVL") == 0 && (*env).shlvl == false)
			|| (ft_strcmp(tmp->var, "HOME") == 0 && (*env).home == false)
			|| (ft_strcmp(tmp->var, "PATH") == 0 && (*env).path == false))
		{
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->value[0] == 0)
			ft_printf("declare -x %s\n", tmp->var);
		else
			ft_print_export_else(tmp->value, tmp);
		tmp = tmp->next;
	}
}

bool	ft_print_export_alone(t_mini *shell, t_env *env)
{
	if (ft_strcmp_shell(shell->tab_pars[shell->tab_index], "export") == 0
		&& shell->tab_pars[shell->tab_index + 1] == NULL)
	{
		ft_print_export(shell, env);
		return (true);
	}
	else if (ft_strcmp_shell(shell->tab_pars[shell->tab_index], "export") == 0
		&& shell->tab_pars[shell->tab_index] != NULL
		&& shell->tab_pars[shell->tab_index + 1] != NULL
		&& (shell->tab_pars[shell->tab_index + 1][0] == '|'
		|| shell->tab_pars[shell->tab_index + 1] == NULL
		|| shell->tab_pars[shell->tab_index + 1][0] == '>'
		|| shell->tab_pars[shell->tab_index + 1][0] == '<'
		|| shell->tab_pars[shell->tab_index + 1][0] == '#'
		|| shell->tab_pars[shell->tab_index + 1][0] == ';'))
	{
		ft_print_export(shell, env);
		return (true);
	}
	return (false);
}
