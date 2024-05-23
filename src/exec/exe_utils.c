#include "../../include/minishell.h"

int	ft_count_quote(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 2 || str[i] == 3)
			j++;
		i++;
	}
	return (j);
}

char	*ft_clean_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - ft_count_quote(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 2 && str[i] != 3)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
