#include "../../include/minishell.h"

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
		|| ft_strchr(just_name_var, '.') != NULL)
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

void	ft_create_list(char **envp, t_mini **shell)
{
	int		len;
	int		i;
	t_envp	*new;

	len = ft_tab_len(envp);
	i = 0;
	while (i < len - 1)
	{
		new = ft_lstnew_envp(envp[i]);
		ft_lstadd_back_envp(shell, new);
		i++;
	}
}

char	**ft_sort_envp(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (envp[i] != NULL)
	{
		temp = envp[i];
		j = i - 1;
		while (j >= 0 && strcmp(envp[j], temp) > 0)
		{
			envp[j + 1] = envp[j];
			j--;
		}
		envp[j + 1] = temp;
		i++;
	}
	return (envp);
}
