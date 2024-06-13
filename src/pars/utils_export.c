#include "../../include/minishell.h"

int	ft_check_last(char *current_arg, t_mini **shell)
{
	if (ft_strlen(current_arg) == 0)
	{
		(*shell)->status = 1;
		syntax_error(INVALID_IDENTIFIER);
		return (2);
	}
	if (current_arg[ft_strlen(current_arg) - 1] == '+')
		return (1);
	return (0);
}

void	ft_check_plus(char **envp, char *just_name_var, char *existing_var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strcmp_shell(ft_find_name_var(envp[i]), just_name_var) != 0)
		i++;
	tmp = ft_strjoin_shell(just_name_var, "=");
	envp[i] = ft_strjoin_shell(tmp, ft_find_value_var(envp[i]));
	envp[i] = ft_strjoin(envp[i], ft_find_value_var(existing_var));
}

static int	ft_check_special_char_two(char *just_name_var)
{
	if (ft_strchr(just_name_var, '{') != NULL
		|| ft_strchr(just_name_var, '}') != NULL)
		return (1);
	if (just_name_var[0] == '$' || ft_strchr(just_name_var, ':') != NULL)
		return (1);
	if (ft_strchr(just_name_var, '*') != NULL
		|| ft_strchr(just_name_var, '-') != NULL)
		return (1);
	if (ft_strchr(just_name_var, '?') != NULL
		|| ft_strchr(just_name_var, '.') != NULL
		|| ft_strchr(just_name_var, '&') != NULL)
		return (1);
	if (ft_strchr(just_name_var, ',') != NULL
		|| ft_strchr(just_name_var, '/') != NULL
		|| ft_strchr(just_name_var, '~') != NULL)
		return (1);
	return (0);
}

static int	ft_check_special_char_one(char *just_name_var)
{
	if (just_name_var[0] >= 48 && just_name_var[0] <= 57)
		return (1);
	if (ft_strchr(just_name_var, '!') != NULL
		|| ft_strchr(just_name_var, '@') != NULL)
		return (1);
	if (ft_strchr(just_name_var, '%') != NULL
		|| ft_strchr(just_name_var, '^') != NULL)
		return (1);
	if (ft_strchr(just_name_var, '(') != NULL
		|| ft_strchr(just_name_var, ')') != NULL)
		return (1);
	if (ft_strchr(just_name_var, '[') != NULL
		|| ft_strchr(just_name_var, ']') != NULL)
		return (1);
	if (ft_check_special_char_two(just_name_var) == 1)
		return (1);
	return (0);
}

int	ft_current_arg(char *current_arg)
{
	char	*just_name_var;

	just_name_var = ft_find_name_var(current_arg);
	if (ft_check_special_char_one(just_name_var) == 1)
		return (1);
	return (0);
}
