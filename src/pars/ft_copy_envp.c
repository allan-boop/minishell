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
	if (!new)
		return (NULL);
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

void	ft_copy_envp(char **envp, t_mini *shell)
{
	int		len;
	t_envp	*new;
	int		i;

	i = 0;
	ft_sort_envp(envp);
	len = ft_tab_len(envp);
	shell->team_envp = NULL;
	while (i < len)
	{
		new = ft_lstnew_envp(envp[i]);
		ft_lstadd_back_envp(&shell, new);
		i++;
	}
	return ;
}
