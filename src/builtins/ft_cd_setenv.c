#include "../../include/minishell.h"

static char	*ft_setenv_index(char *name, char ***envp, char *value, int *i)
{
	int		len;
	char	*new;
	char	*tmp;

	len = ft_strlen(name);
	new = NULL;
	tmp = NULL;
	while ((*envp)[*i] != NULL)
	{
		if (ft_strncmp(name, (*envp)[*i], len) == 0)
		{
			new = ft_strjoin(name, "=");
			tmp = ft_strjoin(new, value);
			free((*envp)[*i]);
			(*envp)[*i] = tmp;
			free(new);
			return (NULL);
		}
		(*i)++;
	}
	return (new);
}

void	ft_setenv(char *name, char *value, char ***envp)
{
	int		i;
	char	*new;
	char	**new_envp;

	i = 0;
	new = ft_setenv_index(name, envp, value, &i);
	if (new == NULL)
		return ;
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	free(new);
	new = ft_strjoin(name, "=");
	new = ft_strjoin(new, value);
	new_envp[i] = new;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}
