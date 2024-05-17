#include "../../include/minishell.h"

void	ft_find_dpointb(int *i, int *start, char **str, char **new)
{
	int	j;

	j = (*i) - 2;
	while ((*str)[j] != '/')
		j--;
	while (*start < j)
	{
		(*new)[0] = (*str)[*start];
		(*start)++;
		(*new)++;
	}
	if ((*str)[*i + 2])
		*i += 3;
	else
		*i += 2;
	*start = *i;
	if ((*str)[*i])
	{
		(*new)[0] = '/';
		(*new)++;
	}
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
