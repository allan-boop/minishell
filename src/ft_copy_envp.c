#include "../include/minishell.h"

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

char	**ft_copy_envp(char **envp)
{
	char	**copy_envp;

	copy_envp = ft_calloc(ft_tab_len(envp) + 1, sizeof(char *));
	if (!copy_envp)
		return (NULL);
	ft_memcpy(copy_envp, envp, ft_tab_len(envp) * sizeof(char *));
	return (copy_envp);
}
