#include "../../include/minishell.h"

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
