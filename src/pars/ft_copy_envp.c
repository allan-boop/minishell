#include "../../include/minishell.h"

static int	ft_tab_len(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

static t_envp	*ft_lstnew_envp(void *content)
{
	t_envp	*new;

	new = ft_alloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->var = content;
	new->tmp_var = NULL;
	new->index = 0;
	new->last_return = 0;
	new->next = NULL;
	return (new);
}

static void	ft_lstadd_back_envp(t_mini **shell, t_envp *new)
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
	while (i < len - 1)
	{
		new = ft_lstnew_envp(envp[i]);
		ft_lstadd_back_envp(&shell, new);
		i++;
	}
	return ;
}
