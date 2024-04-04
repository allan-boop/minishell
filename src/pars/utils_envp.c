#include "../../include/minishell.h"

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
