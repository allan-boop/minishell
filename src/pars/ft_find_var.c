#include "../../include/minishell.h"

char	*ft_find_name_var(char *content)
{
	int		i;
	char	*name_var;

	i = 0;
	if (!content)
		return (NULL);
	while (content[i] && content[i] != '=')
		i++;
	name_var = ft_substr_shell(content, 0, i);
	return (name_var);
}

char	*ft_find_value_var(char *content)
{
	int		i;
	char	*value_var;

	i = 0;
	if (!content)
		return (NULL);
	while (content[i] && content[i] != '=')
		i++;
	value_var = ft_substr_shell(content, i + 1, ft_strlen(content) - i);
	return (value_var);
}
