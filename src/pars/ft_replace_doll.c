#include "../../include/minishell.h"

static char	*ft_replace_doll_in(char *line, char *value)
{
	char	*new_line;

	new_line = ft_alloc(sizeof(char) * (ft_strlen(line)
				+ ft_strlen(value) - 1));
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*ft_replace_doll(char *line, char *value)
{
	char	*new_line;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_line = ft_replace_doll_in(line, value);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
		{
			while (value[k])
				new_line[j++] = value[k++];
			i++;
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
