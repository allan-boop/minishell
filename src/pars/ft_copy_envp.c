#include "../../include/minishell.h"

int	ft_tab_len(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

t_envp	*ft_lstnew_envp(void *content)
{
	t_envp	*new;
	char	*name_var;
	char	*value_var;

	new = ft_alloc(sizeof(t_envp));
	name_var = ft_find_name_var(content);
	value_var = ft_find_value_var(content);
	new->whole_var = content;
	new->var = name_var;
	new->value = value_var;
	new->last_return = 0;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_envp(t_mini **shell, t_envp *new)
{
	t_envp	*last;

	if (!shell)
		return ;
	if (!(*shell)->team_envp)
	{
		(*shell)->team_envp = new;
		return ;
	}
	else
	{
		last = (*shell)->team_envp;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

char	**ft_copy_envp_no_sort(char **envp)
{
	int		len;
	int		i;
	char	**copy_envp;

	i = 0;
	len = ft_tab_len(envp);
	copy_envp = malloc(sizeof(char *) * (len + 1));
	if (!copy_envp)
		return (NULL);
	while (i < len - 1)
	{
		copy_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}

void	ft_copy_envp(t_env *env, t_mini *shell)
{
	int		len;
	t_envp	*new;
	int		i;

	i = 0;
	ft_sort_envp(env);
	len = ft_tab_len((*env).copy_envp);
	shell->team_envp = NULL;
	while (i < len)
	{
		new = ft_lstnew_envp((*env).copy_envp[i]);
		ft_lstadd_back_envp(&shell, new);
		i++;
	}
	return ;
}
